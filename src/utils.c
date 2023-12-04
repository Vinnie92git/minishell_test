/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:12:25 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/04 20:36:40 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*a;
	size_t		i;

	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	a = malloc(sizeof(char) * (len + 1));
	if (a == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start] != '\0')
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strdup(const char	*s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (ptr == NULL)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

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
