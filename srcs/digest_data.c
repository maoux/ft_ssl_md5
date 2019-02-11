/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 19:22:16 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 10:51:50 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** flag : 1 - stdin basic
**		  2 - option p echo stdin
**		  3 - fd is an opened file
*/

static void		double_free(char *s1, char *s2)
{
	ft_strdel(&s1);
	ft_strdel(&s2);
}

static void		print_data(t_cmd_var *var, char *data)
{
	int			i;

	if (var->arg)
		ft_printf(var->arg);
	else
	{
		i = -1;
		while (++i < var->size)
			ft_putchar(data[i]);
	}
}

void			print_digest_aux(t_cmd_var *var, char *data, char *sum)
{
	int			i;

	if (var->opt & FLAG_q)
		ft_printf("%s\n", sum);
	else if (var->opt & FLAG_r)
	{
		ft_printf("%s ", sum);
		print_data(var, var->arg);
		ft_putchar('\n');
	}
	else
	{
		ft_printf("%s (", var->name);
		print_data(var, var->arg);
		ft_printf(") = %s\n", sum);
	}
}

void			print_digest(t_cmd_var *var, int fd, int flag,
							char *(*f)(char *, uint64_t))
{
	char		*data;
	char		*sum;

	if (!(data = get_data(var, fd)))
	{
		var->exit_value = 1;
		return ;
	}
	if (!(sum = f(data, var->size)))
		return ;
	if (flag == 3)
		print_digest_aux(var, data, sum);
	else if (flag == 2)
	{
		print_data(var, data);
		ft_printf("%s\n", sum);
	}
	else if (flag == 1)
		ft_printf("%s\n", sum);
	var->size = 0;
	double_free(data, sum);
}
