/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:15:01 by vini              #+#    #+#             */
/*   Updated: 2024/03/04 11:36:53 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*unquote(char *str)
{
	char	*unquoted;
	int		i;
	int		f_len;

	i = 0;
	f_len = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			f_len += count_flen(str, i);
			i = closing_quote(str, i);
		}
		else
		{
			i++;
			f_len++;
		}
	}
	unquoted = malloc(sizeof(char) * (f_len + 1));
	if (unquoted == NULL)
		return (NULL);
	unquoted = unquoted_str(unquoted, str, 0, 0);
	return (unquoted);
}

void	check_quotes(t_scmd *scmd)
{
	t_token	*aux;

	aux = scmd->wordlist;
	while (aux)
	{
		if (aux->type == WORD || aux->type == FILENAME || aux->type == EOF_N)
			if (ft_strchr(aux->content, '"') || ft_strchr(aux->content, '\''))
				aux->content = unquote(aux->content);
		aux = aux->next;
	}
	free(aux);
}

void	remove_quotes(t_scmd **scmds_list)
{
	t_scmd	*aux;

	aux = *scmds_list;
	while (aux)
	{
		check_quotes(aux);
		aux = aux->next;
	}
	free(aux);
}

char	*buffer_var(char *source, int start, int end, char **env)
{
	char	*expanded;
	char	*varname;
	char	*var;
	int		i;
	int		j;

	varname = ft_substr(source, start, end - start);
	var = find_var(varname, env);
	free (varname);
	expanded = malloc(sizeof(char) * (ft_strlen(source) + ft_strlen(var) + 1));
	if (expanded == NULL)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < start - 1)
		expanded[j] = source[j];
	if (var)
		while (var[i])
			expanded[j++] = var[i++];
	while (source[end])
		expanded[j++] = source[end++];
	expanded[j] = '\0';
	return (expanded);
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
			temp = buffer_var(exp, start, end, env);
			free(exp);
			exp = temp;
			start--;
		}
		else
			start++;
	}
	return (exp);
}
