/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:06:27 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 10:21:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

const uint32_t		g_tab[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9,
	14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10,
	15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

const uint32_t		g_tab_sin[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

/*
** bsize -> bits size of data
** bsize_w_pad -> bits size of data with padding
** csize -> byte size of data
*/

static void			process_loop_md5(t_buffer *tmp, uint32_t *w)
{
	int				j;
	uint32_t		f;
	uint32_t		g;

	j = 0;
	while (j < 64)
	{
		if (j <= 15)
			md5_f1(tmp, &f, &g, j);
		else if (j <= 31)
			md5_f2(tmp, &f, &g, j);
		else if (j <= 47)
			md5_f3(tmp, &f, &g, j);
		else
			md5_f4(tmp, &f, &g, j);
		f = (f + tmp->a + g_tab_sin[j] + w[g]) >> 0;
		tmp->a = tmp->d;
		tmp->d = tmp->c;
		tmp->c = tmp->b;
		tmp->b = (tmp->b + left_rotate32(f, g_tab[j])) >> 0;
		j++;
	}
}

static void			main_loop_md5(t_buffer *buf,
								uint64_t bsize_w_pad,
								char *data_w_pad)
{
	uint32_t		*w;
	t_buffer		tmp;
	int				i;

	i = 0;
	while (i < bsize_w_pad)
	{
		w = (uint32_t *)(data_w_pad + i / CHAR_BIT);
		tmp.a = buf->a;
		tmp.b = buf->b;
		tmp.c = buf->c;
		tmp.d = buf->d;
		process_loop_md5(&tmp, w);
		buf->a = (buf->a + tmp.a) >> 0;
		buf->b = (buf->b + tmp.b) >> 0;
		buf->c = (buf->c + tmp.c) >> 0;
		buf->d = (buf->d + tmp.d) >> 0;
		i += 512;
	}
}

char				*sum_md5(char *data, uint64_t size)
{
	char			*data_w_pad;
	uint64_t		bsize;
	uint64_t		bsize_w_pad;
	t_buffer		buf;

	bsize = size ? (size * CHAR_BIT) : (ft_strlen(data) * CHAR_BIT);
	bsize_w_pad = 0;
	if (bsize % 512 > 448)
		bsize_w_pad = 512;
	bsize_w_pad += bsize + (512 - (bsize % 512));
	if (!(data_w_pad = ft_strnew(bsize_w_pad / CHAR_BIT)))
		return (malloc_failed_md5(NULL));
	data_w_pad = pad_data(data, data_w_pad, bsize, 0);
	buf.a = 0x67452301;
	buf.b = 0xefcdab89;
	buf.c = 0x98badcfe;
	buf.d = 0x10325476;
	main_loop_md5(&buf, bsize_w_pad, data_w_pad);
	ft_strdel(&data_w_pad);
	buf.a = swap_32(buf.a);
	buf.b = swap_32(buf.b);
	buf.c = swap_32(buf.c);
	buf.d = swap_32(buf.d);
	return (buffer_to_string(&buf, 0, "md5"));
}
