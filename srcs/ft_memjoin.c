/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:55:34 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:45:41 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char			*ft_memjoin(char *s1, char *s2, int s1_s, int s2_s)
{
	char		*res;
	int			i;
	int			j;

	if (!(res = (char *)malloc(sizeof(char) * (s1_s + s2_s))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_s)
	{
		res[i] = s1[i];
		i++;
	}
	while (j < s2_s)
	{
		res[i] = s2[j];
		j++;
		i++;
	}
	return (res);
}
