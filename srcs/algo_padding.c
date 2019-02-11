/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_padding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 16:27:10 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 09:22:27 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

static void		print_data(char *data, uint64_t size)
{
	uint64_t	i;
	uint8_t		*w;

	i = 0;
	w = (uint8_t *)data;
	while (i < size / CHAR_BIT)
	{
		ft_printf("%08b ", (uint8_t)(*(data + i)));
		i += 1;
	}
}

static int		pad_data_zero(char *data_w_pad, int *i, int mod)
{
	int			j;

	j = 0;
	if (mod)
	{
		while (j < 512)
		{
			data_w_pad[((*i) + j) / CHAR_BIT] = 0;
			j++;
		}
	}
	while ((*i) % 512 <= 448)
	{
		data_w_pad[((*i) + j) / CHAR_BIT] = 0;
		(*i) += CHAR_BIT;
	}
	if (mod)
	{
		while ((*i) % 512 > 448)
			(*i)--;
	}
	return (j);
}

char			*pad_data(char *data, char *data_w_pad, uint64_t size,
							int endian)
{
	int			i;
	int			j;
	int			mod;
	uint64_t	*data_w_size;

	mod = size % 512 > 448 ? 1 : 0;
	ft_memcpy(data_w_pad, data, size / CHAR_BIT);
	data_w_pad[size / CHAR_BIT] = (char)128;
	i = size + 1 + CHAR_BIT;
	j = pad_data_zero(data_w_pad, &i, mod);
	if (endian)
		data_w_size = (uint64_t *)(&data_w_pad[(i + j) / CHAR_BIT]);
	else
		data_w_size = (uint64_t *)(&data_w_pad[(i + j) / CHAR_BIT]);
	*data_w_size = (endian ? swap_64(size) : size) >> 0;
	return (data_w_pad);
}
