/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 12:04:08 by heynard           #+#    #+#             */
/*   Updated: 2019/02/09 13:03:16 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t		left_rotate32(uint32_t x, uint32_t y)
{
	return ((x << y) | (x >> (32 - y)));
}

uint32_t		right_rotate32(uint32_t x, uint32_t y)
{
	return ((x >> y) | (x << (32 - y)));
}

uint32_t		ch(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (~(x) & z));
}

uint32_t		maj(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) ^ (x & z) ^ (y & z));
}
