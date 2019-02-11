/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:32:32 by heynard           #+#    #+#             */
/*   Updated: 2019/02/07 18:05:00 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char				*ft_itoa_base_l(uint32_t value, int base)
{
	int				i;
	char			*nbr;

	i = 8;
	nbr = (char *)malloc(sizeof(char) * 9);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	return (nbr);
}

char				*ft_itoa_base(int value, int base)
{
	char			*str;
	int				neg;
	int				i;

	neg = 0;
	i = 1;
	if (value < 0)
	{
		if (base == 10)
			neg = 1;
		value *= -1;
	}
	while (ft_power(base, i) - 1 < value)
		i++;
	str = (char *)malloc(sizeof(char) * i);
	str[i + neg] = '\0';
	while (i-- > 0)
	{
		str[i + neg] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		value /= base;
	}
	if (neg)
		str[0] = '-';
	ft_printf("%s\n", str);
	return (str);
}
