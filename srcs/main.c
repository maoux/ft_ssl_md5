/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 17:53:32 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:49:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** digest_prog :handle options r p q s
**				need algorithm to perform as char *(*f)(char *, uint64_t)
**				beware ! digest_prog frees the algorithm returned string
*/

t_command		g_commands[] = {
	{"md5", &digest_prog, &sum_md5},
	{"sha256", &digest_prog, &sum_sha256},
	{"default", NULL, NULL}
};

static int		ft_ssl_usage(void)
{
	ft_dprintf(STDERR_FILENO, "usage: ft_ssl command "
								"[command opts] [command args]\n");
	return (1);
}

static int		ft_ssl_usage_commands(char *wrong_cmd)
{
	ft_dprintf(STDERR_FILENO, "ft_ssl: Error: '%s' is an "
								"invalid command.\n\n"
								"Standard commands:\n\n"
								"Message Digest commands:\n"
								"md5\nsha256\n\n"
								"Cipher commands:\n", wrong_cmd);
	return (1);
}

int				main(int ac, char **av)
{
	int			index;

	if (ac < 2)
		return (ft_ssl_usage());
	if ((index = get_command_index(av[1], get_nb_commands())) == -1)
		return (ft_ssl_usage_commands(av[1]));
	return (g_commands[index].command(av[1], ac, av, g_commands[index].algo));
}
