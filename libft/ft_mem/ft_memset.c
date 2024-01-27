/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:23:01 by vipalaci          #+#    #+#             */
/*   Updated: 2023/04/09 15:11:15 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_mem/ft_mem.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned int	i;
	unsigned char	*cast_b;

	cast_b = (unsigned char *)b;
	i = 0;
	while (len > 0)
	{
		cast_b[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (cast_b);
}
