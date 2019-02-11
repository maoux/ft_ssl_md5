/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_usages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 16:26:57 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:26:51 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			usage_option_s(t_cmd_var *var)
{
	ft_dprintf(STDERR_FILENO, "ft_ssl: %s: option requires an argument -- s\n"
				"usage: ft_ssl md5 [-pqr] [-s string] [files ...]\n",
				var->name);
	var->exit_value = 1;
	return (free_cmd_var(var));
}

int			usage_options(t_cmd_var *var, char wrong_opt)
{
	var->exit_value = 1;
	ft_dprintf(STDERR_FILENO, "ft_ssl: %s: illegal option -- %c\n"
				"usage: ft_ssl md5 [-pqr] [-s string] [files ...]\n",
				var->name, wrong_opt);
	return (1);
}

char		*malloc_failed(void *data, const char *algo)
{
	if (data)
		free(data);
	ft_dprintf(STDERR_FILENO, "ft_ssl: %s: Malloc failed\n", algo);
	return (NULL);
}

char		*malloc_failed_sha256(void *data)
{
	if (data)
		free(data);
	ft_dprintf(STDERR_FILENO, "ft_ssl: sha256: Malloc failed\n");
	return (NULL);
}

char		*malloc_failed_md5(void *data)
{
	if (data)
		free(data);
	ft_dprintf(STDERR_FILENO, "ft_ssl: md5: Malloc failed\n");
	return (NULL);
}
