/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:58:06 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/29 10:51:11 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char	*ft_strjoin_ms(char *s1, char *s2)
// {
// 	char	*ptr;

// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(1 * sizeof(char));
// 		s1[0] = '\0';
// 	}
// 	if (!s1 || !s2)
// 		return (NULL);
// 	ptr = (char *)malloc(1 + ft_strlen(s1) + ft_strlen(s2) * sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	ptr = ft_join_ms(ptr, s1, s2);
// 	free(s1);
// 	return (ptr);
// }

// char	*ft_join_ms(char *dest, char *s1, char *s2)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (s1 && s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2 && s2[j])
// 	{
// 		dest[i + j] = s2[j];
// 		j++;
// 	}
// 	dest[i + j] = '\0';
// 	return (dest);
// }