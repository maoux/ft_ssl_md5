/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:33:08 by heynard           #+#    #+#             */
/*   Updated: 2019/02/06 12:20:20 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_cmd_var			*init_cmd_var(void)
{
	t_cmd_var		*new;

	if (!(new = (t_cmd_var *)malloc(sizeof(t_cmd_var))))
		return (new);
	new->opt = 0;
	new->exit_value = 0;
	new->std_in = 1;
	new->std_in_p = 0;
	new->arg = NULL;
	new->name = NULL;
	new->size = 0;
	return (new);
}

int					free_cmd_var(t_cmd_var *var)
{
	int				tmp;

	if (var)
	{
		if (var->name)
			ft_strdel(&var->name);
		tmp = var->exit_value;
		free(var);
		return (tmp);
	}
	return (1);
}
