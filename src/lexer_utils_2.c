/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:31:42 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/20 14:03:10 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var(char *varname, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname)) &&
			env[i][ft_strlen(varname)] == '=')
			return (env[i] + (ft_strlen(varname) + 1));
		i++;
	}
	return (NULL);
}

char	*quoted_dsign(char *str, char **env)
{
	char	*expanded;
	char	*varname;
	char	*var;
	int		start;
	int		i;
	int		j;

	expanded = malloc(sizeof(char) * 1024);
	if (expanded == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			start = i;
			while (str[i] && !is_space(str[i]) && !is_operator(str[i])
				&& !is_quote(str[i]) && !is_dsign(str[i]))
				i++;
			varname = ft_substr(str, start, i - start);
			var = find_var(varname, env);
			if (var != NULL)
			{
				expanded = ft_strjoin(expanded, var);
				j += ft_strlen(var);
			}
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}
