/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:28:30 by heynard           #+#    #+#             */
/*   Updated: 2019/02/05 10:39:49 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double		ft_fmod(double x, double y)
{
	return (x - (int)(x / y) * y);
}

int			ft_floor(double x)
{
	return ((int)(x - ft_fmod(x, 1.0)));
}
