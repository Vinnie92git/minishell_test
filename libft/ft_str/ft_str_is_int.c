/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:07:29 by vinni             #+#    #+#             */
/*   Updated: 2023/04/10 20:43:50 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_str/ft_str.h"

int	ft_str_is_int(char *str)
{
	int	sign;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	if (ft_atoi(str) * sign > INT_MAX || ft_atoi(str) * sign < INT_MIN)
		return (0);
	return (1);
}
