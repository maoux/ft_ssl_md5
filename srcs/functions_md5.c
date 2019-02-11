/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_md5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 20:49:18 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:27:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

void		md5_f1(t_buffer *tmp, uint32_t *f, uint32_t *g, int j)
{
	*f = (tmp->b & tmp->c) | (~(tmp->b) & tmp->d);
	*g = j;
}

void		md5_f2(t_buffer *tmp, uint32_t *f, uint32_t *g, int j)
{
	*f = (tmp->d & tmp->b) | (~(tmp->d) & tmp->c);
	*g = (5 * j + 1) % 16;
}

void		md5_f3(t_buffer *tmp, uint32_t *f, uint32_t *g, int j)
{
	*f = tmp->b ^ tmp->c ^ tmp->d;
	*g = (3 * j + 5) % 16;
}

void		md5_f4(t_buffer *tmp, uint32_t *f, uint32_t *g, int j)
{
	*f = tmp->c ^ (tmp->b | ~(tmp->d));
	*g = (7 * j) % 16;
}
