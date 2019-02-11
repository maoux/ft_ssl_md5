/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_to_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 13:28:27 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:47:10 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

static void		double_free(char *s1, char *s2)
{
	ft_strdel(&s1);
	ft_strdel(&s2);
}

static char		*free_malloc_failed(void *data, char *to_free, const char *algo)
{
	ft_strdel(&to_free);
	return (malloc_failed(data, algo));
}

static char		*buffer_to_string_last(t_buffer *buf, const char *algo,
									char *res)
{
	char		*tmp1;
	char		*tmp2;

	if (!(tmp1 = ft_itoa_base_l(buf->h, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	return (res);
}

static char		*buffer_to_string_ex(t_buffer *buf, const char *algo,
									char *res)
{
	char		*tmp1;
	char		*tmp2;

	if (!(tmp1 = ft_itoa_base_l(buf->e, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	if (!(tmp1 = ft_itoa_base_l(buf->f, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	if (!(tmp1 = ft_itoa_base_l(buf->g, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	return (buffer_to_string_last(buf, algo, res));
}

char			*buffer_to_string(t_buffer *buf, int flag, const char *algo)
{
	char		*res;
	char		*tmp1;
	char		*tmp2;

	if (!(tmp1 = ft_itoa_base_l(buf->a, 16)))
		return (malloc_failed(NULL, algo));
	if (!(tmp2 = ft_itoa_base_l(buf->b, 16)))
		return (malloc_failed(NULL, algo));
	if (!(res = ft_strjoin(tmp1, tmp2)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	if (!(tmp1 = ft_itoa_base_l(buf->c, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	if (!(tmp1 = ft_itoa_base_l(buf->d, 16)))
		return (malloc_failed(NULL, algo));
	tmp2 = res;
	if (!(res = ft_strjoin(res, tmp1)))
		return (free_malloc_failed((void *)tmp2, tmp1, algo));
	double_free(tmp1, tmp2);
	return (flag ? buffer_to_string_ex(buf, algo, res) : res);
}
