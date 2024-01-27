/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:55:01 by vipalaci          #+#    #+#             */
/*   Updated: 2023/04/09 15:41:35 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_others/ft_others.h"

static int	ft_count_strings(char const *s, char c)
{
	int	i;
	int	string_count;

	i = 0;
	string_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			string_count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else if (s[i] == c)
			i++;
	}
	return (string_count);
}

static char	*ft_copy(const char *s, int start, int end)
{
	int		i;
	char	*string;

	string = malloc(sizeof(char) * (end - start + 1));
	if (string == NULL)
		return (string);
	i = 0;
	while (start < end)
	{
		string[i] = s[start];
		i++;
		start++;
	}
	string[i] = '\0';
	return (string);
}

static char	**ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free (s[i]);
		i++;
	}
	free (s);
	return (NULL);
}

static char	**ft_fill_matrix(char **m, char const *s, char c)
{
	size_t	pos;
	size_t	j;
	int		index;

	pos = 0;
	j = 0;
	index = -1;
	while (pos <= ft_strlen(s))
	{
		if (s[pos] != c && index < 0)
			index = pos;
		else if ((s[pos] == c || pos == ft_strlen(s)) && index >= 0)
		{
			m[j] = ft_copy(s, index, pos);
			if (!m[j])
				return (ft_free(m));
			index = -1;
			j++;
		}
		pos++;
	}
	m[j] = 0;
	return (m);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;

	matrix = malloc(sizeof(char *) * (ft_count_strings(s, c) + 1));
	if (matrix == NULL)
		return (matrix);
	return (ft_fill_matrix(matrix, s, c));
}
