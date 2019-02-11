/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_sha256.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:18:38 by heynard           #+#    #+#             */
/*   Updated: 2019/02/09 13:28:55 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "digest.h"

uint32_t			sig0(uint32_t x)
{
	return (right_rotate32(x, 2) ^ right_rotate32(x, 13)
			^ right_rotate32(x, 22));
}

uint32_t			sig1(uint32_t x)
{
	return (right_rotate32(x, 6) ^ right_rotate32(x, 11)
			^ right_rotate32(x, 25));
}

uint32_t			sig2(uint32_t x)
{
	return (right_rotate32(x, 7) ^ right_rotate32(x, 18) ^ (x >> 3));
}

uint32_t			sig3(uint32_t x)
{
	return (right_rotate32(x, 17) ^ right_rotate32(x, 19) ^ (x >> 10));
}
