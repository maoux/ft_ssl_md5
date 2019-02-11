/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:45:03 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:25:21 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

const uint32_t		g_tab_pr[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void			rotate_sha256(t_buffer *tmp, int i, uint32_t *w)
{
	uint32_t		t1;
	uint32_t		t2;

	t1 = (tmp->h + sig1(tmp->e) + ch(tmp->e, tmp->f, tmp->g)
		+ g_tab_pr[i] + w[i]) >> 0;
	t2 = (sig0(tmp->a) + maj(tmp->a, tmp->b, tmp->c)) >> 0;
	tmp->h = tmp->g;
	tmp->g = tmp->f;
	tmp->f = tmp->e;
	tmp->e = (tmp->d + t1) >> 0;
	tmp->d = tmp->c;
	tmp->c = tmp->b;
	tmp->b = tmp->a;
	tmp->a = (t1 + t2) >> 0;
}

static void			init_buffer(t_buffer *buf, t_buffer *tmp)
{
	tmp->a = buf->a;
	tmp->b = buf->b;
	tmp->c = buf->c;
	tmp->d = buf->d;
	tmp->e = buf->e;
	tmp->f = buf->f;
	tmp->g = buf->g;
	tmp->h = buf->h;
}

static void			add_buffer(t_buffer *buf, t_buffer *tmp)
{
	buf->a = (buf->a + tmp->a) >> 0;
	buf->b = (buf->b + tmp->b) >> 0;
	buf->c = (buf->c + tmp->c) >> 0;
	buf->d = (buf->d + tmp->d) >> 0;
	buf->e = (buf->e + tmp->e) >> 0;
	buf->f = (buf->f + tmp->f) >> 0;
	buf->g = (buf->g + tmp->g) >> 0;
	buf->h = (buf->h + tmp->h) >> 0;
}

static void			main_loop_sha256(t_buffer *buf,
									char *data_w_pad,
									uint64_t bsize_w_pad)
{
	t_buffer		tmp;
	uint32_t		w[64];
	uint64_t		offset;
	int				i;

	offset = 0;
	while (offset < bsize_w_pad)
	{
		i = -1;
		while (++i < 16)
			w[i] = swap_32(((uint32_t *)(data_w_pad + offset / CHAR_BIT))[i]);
		while (i < 64)
		{
			w[i] = sig3(w[i - 2]) + w[i - 7] + sig2(w[i - 15]) + w[i - 16];
			i++;
		}
		init_buffer(buf, &tmp);
		i = 0;
		while (i < 64)
			rotate_sha256(&tmp, i++, w);
		add_buffer(buf, &tmp);
		offset += 512;
	}
}

char				*sum_sha256(char *data, uint64_t size)
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
		return (malloc_failed_sha256(NULL));
	data_w_pad = pad_data(data, data_w_pad, bsize, 1);
	buf.a = 0x6a09e667;
	buf.b = 0xbb67ae85;
	buf.c = 0x3c6ef372;
	buf.d = 0xa54ff53a;
	buf.e = 0x510e527f;
	buf.f = 0x9b05688c;
	buf.g = 0x1f83d9ab;
	buf.h = 0x5be0cd19;
	main_loop_sha256(&buf, data_w_pad, bsize_w_pad);
	ft_strdel(&data_w_pad);
	return (buffer_to_string(&buf, 1, "sha256"));
}
