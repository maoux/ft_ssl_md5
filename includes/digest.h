/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:46:51 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:58:19 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIGEST_H
# define DIGEST_H

struct			s_digest_buffer
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
};

typedef struct s_digest_buffer	t_buffer;

char			*buffer_to_string(t_buffer *buf, int flag, const char *algo);

void			md5_f1(t_buffer *tmp, uint32_t *f, uint32_t *g, int j);
void			md5_f2(t_buffer *tmp, uint32_t *f, uint32_t *g, int j);
void			md5_f3(t_buffer *tmp, uint32_t *f, uint32_t *g, int j);
void			md5_f4(t_buffer *tmp, uint32_t *f, uint32_t *g, int j);

uint32_t		left_rotate32(uint32_t x, uint32_t y);
uint32_t		right_rotate32(uint32_t x, uint32_t y);

#endif
