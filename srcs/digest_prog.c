/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_prog.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:35:42 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 10:09:08 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		print_digest_p(t_cmd_var *var, char *(*f)(char *, uint64_t))
{
	char		*sum;

	if (!(sum = f(var->arg, var->size)))
		return (1);
	if (var->opt & FLAG_q)
		ft_printf("%s\n", sum);
	else if (var->opt & FLAG_r)
		ft_printf("%s \"%s\"\n", sum, var->arg);
	else
		ft_printf("%s (\"%s\") = %s\n", var->name, var->arg, sum);
	ft_strdel(&sum);
	return (0);
}

static void		handle_current_arg(t_cmd_var *var, char *(*f)(char *, uint64_t))
{
	ft_strtoupper(var->name);
	if (var->arg)
	{
		if (print_digest_p(var, f))
			var->exit_value = 1;
		var->opt &= ~FLAG_s;
		var->arg = NULL;
		var->std_in = 0;
	}
	if (var->opt & FLAG_p)
	{
		if (var->std_in_p)
			ft_printf("%s\n", f("", 0));
		else
			print_digest(var, 0, 2, f);
		var->opt &= ~FLAG_p;
		var->std_in_p = 1;
	}
	ft_strtolower(var->name);
}

int				digest_prog(char *str, int ac, char **av,
							char *(*f)(char *, uint64_t))
{
	t_cmd_var	*var;
	int			i;

	if (!(var = init_cmd_var()))
		return (ft_dprintf(STDERR_FILENO, "ft_ssl: %s: Malloc failed\n", str));
	i = 1;
	if (!(var->name = ft_strdup(str)))
	{
		ft_dprintf(STDERR_FILENO, "ft_ssl: %s: Malloc failed\n", str);
		var->exit_value = 1;
		return (free_cmd_var(var));
	}
	while (++i < ac)
	{
		if (handle_next_arg(var, av[i], f) == 1)
			return (free_cmd_var(var));
		handle_current_arg(var, f);
	}
	if (var->opt & FLAG_s && !var->arg)
		return (usage_option_s(var));
	if (var->std_in && var->std_in_p && var->opt != 0 && var->opt != FLAG__)
		ft_printf("%s\n", f("", 0));
	else if (var->std_in && !var->std_in_p)
		print_digest(var, 0, 1, f);
	return (free_cmd_var(var));
}
