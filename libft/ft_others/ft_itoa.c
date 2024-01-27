/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:32:10 by vipalaci          #+#    #+#             */
/*   Updated: 2023/04/09 15:33:30 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_others/ft_others.h"

static int	ft_count(long int i)
{
	int	count;

	count = 0;
	if (i <= 0)
	{
		i = i * -1;
		count++;
	}
	while (i > 0)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			count;
	long int	number;

	number = n;
	count = ft_count(number);
	ptr = malloc(sizeof(char) * count + 1);
	if (ptr == NULL)
		return (ptr);
	ptr[count--] = '\0';
	if (number == 0)
		ptr[0] = '0';
	if (number < 0)
	{
		ptr[0] = '-';
		number = number * -1;
	}
	while (number > 0)
	{
		ptr[count--] = number % 10 + '0';
		number = number / 10;
	}
	return (ptr);
}
