/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:36:14 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:54:18 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>

static void		read_error_messages(t_cmd_var *var, int fd)
{
	ft_strtolower(var->name);
	if (errno == EISDIR)
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: can't read a directory\n",
				var->name);
	}
	else if (errno == EBADF)
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: trying to read an invalid "
				"file descriptor\n", var->name);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: an error occurred while"
				"reading in %d\n", var->name, fd);
	}
}

static char		*get_data_aux(t_cmd_var *var, char *res, char buffer[2048],
								unsigned int fd)
{
	char		*tmp;

	tmp = res;
	res = ft_memjoin(res, buffer, var->size, var->code);
	ft_strdel(&tmp);
	if (!res)
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: malloc failed"
				"while reading %d\n", var->name, fd);
		var->exit_value = 1;
		return (NULL);
	}
	return (res);
}

static char		*free_res_error(t_cmd_var *var, char *res, unsigned int fd)
{
	read_error_messages(var, fd);
	ft_strdel(&res);
	return (NULL);
}

char			*get_data(t_cmd_var *var, unsigned int fd)
{
	char		buffer[2048];
	char		*res;
	int			code;

	res = NULL;
	var->size = 0;
	while ((code = read(fd, buffer, 2048)) > 0)
	{
		var->code = code;
		if (!(res = get_data_aux(var, res, buffer, fd)))
			return (NULL);
		var->size += code;
	}
	if (res == NULL)
	{
		if (!(res = (char *)malloc(1)))
			return (NULL);
		res[0] = '\0';
	}
	if (code == -1)
		return (free_res_error(var, res, fd));
	return (res);
}
