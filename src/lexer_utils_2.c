/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:15:36 by vini              #+#    #+#             */
/*   Updated: 2024/02/14 10:52:08 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var(char *varname, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(varname, env[i], ft_strlen(varname))
			&& env[i][ft_strlen(varname)] == '=')
			return (env[i] + (ft_strlen(varname) + 1));
		i++;
	}
	return (0);
}

char	*expand(char *source, int start, int end, char **env)
{
	char	*expand;
	char	*varname;
	char	*var;
	int		i;
	int		j;

	varname = ft_substr(source, start, end - start);
	var = find_var(varname, env);
	free (varname);
	expand = malloc(sizeof(char) * (ft_strlen(source) + ft_strlen(var) + 1));
	if (expand == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < start - 1)
	{
		expand[j] = source[j];
		j++;
	}
	while (var[i])
		expand[j++] = var[i++];
	while (source[end])
		expand[j++] = source[end++];
	expand[j] = '\0';
	return (expand);
}

char	*quoted_dsign(char *str, char **env)
{
	char	*exp;
	char	*temp;
	int		start;
	int		end;

	exp = ft_strdup(str);
	start = 0;
	while (exp[start])
	{
		if (is_dsign(exp[start]))
		{
			start++;
			end = start;
			while (exp[end] && !is_space(exp[end]) && !is_operator(exp[end])
				&& !is_quote(exp[end]) && !is_dsign(exp[end]))
				end++;
			temp = expand(exp, start, end, env);
			free(exp);
			exp = temp;
			start--;
		}
		else
			start++;
	}
	return (exp);
}
