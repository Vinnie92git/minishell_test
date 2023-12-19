/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:31:42 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/19 22:36:19 by vini             ###   ########.fr       */
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
			return (env[i] + (ft_strlen(var) + 1));
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
			varname = ft_substr(str, i, i - start);
			var = find_var(varname, env);
			
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

// char	*quoted_dsign(char *str, char **env)
// {
// 	char	**varnames;
// 	char	**vars;
// 	int		i;
// 	int		j;
// 	int		end;

// 	i = 0;
// 	j = 0;
// 	end = 0;
// 	while (str[i++])
// 		if (is_dsign(str[i]))
// 			return (str);
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] != '$')
// 			i++;
// 		i++;
// 		end = i;
// 		while (str[i] && !is_space(str[i]) && !is_operator(str[i])
// 			&& !is_quote(str[i]) && !is_dsign(str[i]))
// 			end++;
// 		varnames[j] = ft_substr(str, i, end - i);
// 		j++;
// 		i = end;
// 	}
// 	varnames[j] = '\0';
// 	j = 0;
// 	while (varnames[j])
// 	{
// 		vars[j] = find_var(varnames[j], env);
// 		j++;
// 	}
// 	return (expand_quotes(str, vars, varnames));
// }

// char	*expand_quotes(char *str, char **vars, char **varnames)
// {
// 	char	*expanded;
// 	int		sum_1;
// 	int		sum_2;
// 	int		i;
// 	int		j;
// 	int		k;

// 	sum_1 = 0;
// 	sum_2 = 0;
// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (varnames[i])
// 	{
// 		sum_1 += ft_strlen(varnames[i]);
// 		i++;
// 	}
// 	i = 0;
	
// 	expanded = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(var) - sum));
// 	while (str[i])
// 	{
// 		while (str[i] != '$')
// 		{
// 			expanded[j] = str[i];
// 			i++;
// 			j++;
// 		}
// 		while (var[k])
// 		{
// 			expanded[j] = var[k]
// 			k++;
// 			j++;
// 		}
// 	}
// }