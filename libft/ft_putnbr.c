/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlongfel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 12:08:19 by xlongfel          #+#    #+#             */
/*   Updated: 2019/09/18 13:12:30 by xlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int i)
{
	int			ti;
	char		c[60];
	long long	z;
	char		a;

	ti = 0;
	z = i;
	if (i < 0)
	{
		write(1, "-", 1);
		z = z * (-1);
	}
	if (i == 0)
		write(1, "0", 1);
	while (z > 0)
	{
		a = z % 10;
		z = z / 10;
		c[ti] = a + '0';
		ti++;
	}
	while (ti)
		write(1, &c[ti-- - 1], 1);
}
