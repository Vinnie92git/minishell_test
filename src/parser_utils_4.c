/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 22:03:54 by vini              #+#    #+#             */
/*   Updated: 2024/02/20 18:22:32 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	j = -1;
	while (++j < start - 1)
		expand[j] = source[j];
	if (var)
		while (var[i])
			expand[j++] = var[i++];
	while (source[end])
		expand[j++] = source[end++];
	expand[j] = '\0';
	return (expand);
}

char	*expand_dsign(char *str, char **env)
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

char*	check_quotes(char *str, char **env)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while(str[i])
	{
		if (is_quote(str[i]))
		{
			quote = is_quote(str[i]);
			if (quote == DOUBLE_QUOTE)
				str = quoted_dsign(str, env, i);
			i = closing_quote(str, i);
		}
		else if (str[i] == '$')
			str = expand_dsign(str, env);
		else
			i++;
	}
	return (str);
}

void	check_dsign(t_scmd *scmd, char **env)
{
	t_token	*aux;

	aux = scmd->wordlist;
	while (aux)
	{
		if (aux->type == WORD || aux->type == QUOTED_WORD)
			if (ft_strchr(aux->content, '$'))
				aux->content = check_quotes(aux->content, env);
		aux = aux->next;
	}
}

void	expand_var(t_scmd **scmds_list, char **env)
{
	t_scmd	*aux;

	aux = *scmds_list;
	while (aux)
	{
		check_dsign(aux, env);
		aux = aux->next;
	}
}