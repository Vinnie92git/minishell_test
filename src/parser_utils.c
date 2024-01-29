/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:30:55 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/29 14:11:19 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redir(int type)
{
	if (type == IN_REDIR || type == OUT_REDIR
		|| type == HEREDOC || type == APPEND)
		return (1);
	return (0);
}

int	check_pipe(t_token *token)
{
	if (!token)
		return  (0);
	if (token->type == PIPE)
		return (0);
	return (1);
}

int	check_redir(t_token *token)
{
	if (!token)
		return  (0);
	if (is_redir(token->type))
		return (0);
	return (1);
}

int	check_syntax(t_token **token_list)
{
	t_token	*aux;

	aux = *token_list;
	if (aux->type == PIPE)
		return (PARSE_ERR);
	while (aux)
	{
		if (aux->type == PIPE)
		{
			aux = aux->next;
			if (!check_pipe(aux))
				return (PARSE_ERR);
		}
		else if (is_redir(aux->type))
		{
			aux = aux->next;
			if (!check_redir(aux))
				return (PARSE_ERR);
			if (aux->type == PIPE)
				return (PARSE_ERR);
		}
		aux = aux->next;
	}
	return (1);
}
