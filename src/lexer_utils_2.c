/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:31:42 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/22 13:44:26 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_var(const char *varname, const char **env)
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
	return ("");
}

/**
 * quoted_dsign
 * @param source
 * @param start start next expand
 * @param len lend next expand
 * @param source
*/
char	*quoted_dsign(char *source, int start, int len, char **env)
{
	char	*expand;
	char	*varname;
	char	*var;
	// int		start_old;
	int		j;
	
	expand = NULL;
	// start++;
	// start_old = start;
	// while (source[start] && !is_space(source[start]) && !is_operator(source[start])
	// 	&& !is_quote(source[start]) && !is_dsign(source[start]))
	// 	start++;
	varname = ft_substr(source, start, len);
	var = find_var(varname, env);
	free (varname);
	expand = malloc(sizeof(char) * (ft_strlen(source) + ft_strlen(var) + 1));
	
	if (expand == NULL)
		return (NULL);
	j = -1;
	while (j++ < start)
		expand[j] = source[j];
	while (*var != '\0')
	{
		expand[j++] = *var;
		var++;
	}
	while (source)
	{
		expand[j] = 
	}
	// if (var != NULL)
	// {
	// 	expand = ft_strjoin(expanded, var);
	// 	j += ft_strlen(var);
	// }
	expand[j] = '\0';
	free(source);
	return (expand);
}

char	*quoted_dsign_all(const char *str, const char **env)
{
	char	*expanded;
	char	*temp;
	// char	*varname;
	// char	*var;
	// int		start;
	// int		i;
	// int		j;
	int		start; //start next expand
	int		len; //lend next expand

	expanded = ft_strdup(str);
	start = 0;
	while (expanded[start])
	{
		if (is_dsign(expanded[start]))
		{
			len = start;
			while (expanded[start] && !is_space(expanded[start]) && !is_operator(expanded[start])
				&& !is_quote(expanded[start]) && !is_dsign(expanded[start]))
				len++;
			temp = quoted_dsign(expanded, start, len, env);
			free(expanded);
			expanded = temp;
		}	
		// if (is_dsign(str[i]))
		// {
		// 	i++;
		// 	start = i;
		// 	while (str[i] && !is_space(str[i]) && !is_operator(str[i])
		// 		&& !is_quote(str[i]) && !is_dsign(str[i]))
		// 		i++;
		// 	varname = ft_substr(str, start, i - start);
		// 	var = find_var(varname, env);
		// 	if (var != NULL)
		// 	{
		// 		expanded = ft_strjoin(expanded, var);
		// 		j += ft_strlen(var);
		// 	}
		// }
		// else
		// {
		// 	expanded[j] = str[i];
		// 	j++;
		// 	i++;
		// }
	}
	expanded[j] = '\0';
	return (expanded);
}
