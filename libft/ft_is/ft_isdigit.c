/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:19:42 by vipalaci          #+#    #+#             */
/*   Updated: 2023/04/09 13:55:34 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_is/ft_is.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int	main()
{
	int c = '0';
	printf("%d", ft_isdigit(c));
	return (0);
}
*/