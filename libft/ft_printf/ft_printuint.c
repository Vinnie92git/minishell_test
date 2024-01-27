/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:08:54 by vinni             #+#    #+#             */
/*   Updated: 2023/04/10 19:12:30 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"

void	ft_printunsigned(unsigned int n)
{
	if (n > 9)
		ft_printuint(n / 10);
	if (n <= 9)
	{
		ft_putchar_fd(n + '0', 1);
		return ;
	}
	ft_putchar_fd((n % 10) + '0', 1);
}

int	ft_printuint(unsigned int nbr)
{
	int	len;

	len = 0;
	ft_printunsigned(nbr);
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}
