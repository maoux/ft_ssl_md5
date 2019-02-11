/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 21:40:41 by heynard           #+#    #+#             */
/*   Updated: 2019/01/27 22:11:30 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					get_nb_commands(void)
{
	int				i;

	i = 0;
	while (ft_strcmp(g_commands[i].name, "default"))
		i++;
	return (i);
}

int					get_command_index(char *cmd, int nbc)
{
	int				i;

	i = 0;
	while (i < nbc)
	{
		if (!ft_strcmp(g_commands[i].name, cmd))
			return (i);
		i++;
	}
	return (-1);
}
