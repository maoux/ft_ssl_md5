/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 13:55:29 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 10:08:40 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>

static int		open_error_messages(t_cmd_var *var, char *arg)
{
	if (errno == EACCES)
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s: Permission denied\n",
				var->name, arg);
	}
	else if (errno == EISDIR)
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s: Is a directory\n",
				var->name, arg);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: %s: No such file or "
				"directory\n", var->name, arg);
	}
	var->exit_value = 1;
	return (0);
}

/*
** usage_options print error and return non zero value for cascade
** interruption
*/

static int		parse_options(t_cmd_var *var, char *arg)
{
	int			i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'q')
			var->opt |= FLAG_q;
		else if (arg[i] == 'r')
			var->opt |= FLAG_r;
		else if (arg[i] == 'p')
			var->opt |= FLAG_p;
		else if (arg[i] == 's')
		{
			var->opt |= FLAG_s;
			if (arg[i + 1] != '\0')
				var->arg = &arg[i + 1];
			return (0);
		}
		else if (arg[i] == '-' && i == 1 && arg[2] == '\0')
			var->opt |= FLAG__;
		else
			return (usage_options(var, arg[i]));
	}
	return (0);
}

/*
**	return 0 on success 1 on failure (malloc error , etc)
*/

int				handle_next_arg(t_cmd_var *var, char *arg,
								char *(*f)(char *, uint64_t))
{
	int			fd;

	if (arg)
	{
		if (var->opt & FLAG_s)
		{
			var->arg = arg;
			return (0);
		}
		if (!(var->opt & FLAG__) && arg[0] == '-' && (ft_strlen(arg) != 1))
			return (parse_options(var, arg));
		var->opt |= FLAG__;
		var->std_in = 0;
		if ((fd = open(arg, O_RDONLY)) < 0)
			return (open_error_messages(var, arg));
		var->arg = arg;
		ft_strtoupper(var->name);
		print_digest(var, fd, 3, f);
		ft_strtolower(var->name);
		var->arg = NULL;
		if (close(fd) < 0)
			return (open_error_messages(var, arg));
		return (0);
	}
	return (1);
}
