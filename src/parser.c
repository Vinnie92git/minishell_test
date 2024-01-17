/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/17 17:12:00 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_redir(t_scmd	*scmd)
{
	int	i;

	i = 0;
	while (scmd->words[i])
	{
		
	}
}

int	find_redir(t_scmd **scmds_list)
{
	t_scmd	*aux;
	int		i;

	aux = *scmds_list;
	while (aux)
	{
		check_redir(aux);
		aux = aux->next;
	}
}

t_token	*create_scmd(t_token *token, t_scmd **scmds_list)
{
	t_scmd	*simple_cmd;
	t_token	*aux;
	int		i;

	simple_cmd = ms_cmdnew();
	aux = token;
	i = 0;
	while (aux && aux->type != PIPE)
	{
		simple_cmd->word_count++;
		aux = aux->next;
	}
	simple_cmd->words = malloc(sizeof(char *) * (simple_cmd->word_count + 1));
	if (!simple_cmd->words)
		return (NULL);
	while (token && token->type != PIPE)
	{
		simple_cmd->words[i] = ft_strdup(token->content);
		i++;
		token = token->next;
	}
	simple_cmd->words[i] = NULL;
	ms_cmdadd_back(scmds_list, simple_cmd);
	return (token);
}

int	build_scmdlist(t_token **token_list, t_scmd **scmds_list)
{
	t_token	*aux;
	
	aux = *token_list;
	while (aux)
	{
		if (aux->type == PIPE)
		{
			aux = aux->next;
			if (aux->type == PIPE)
				return (PARSE_ERR);
		}
		aux = create_scmd(aux, scmds_list);
	}
	return (1);
}

int	parser(t_token **token_list, t_scmd **scmds_list)
{
	int	err;

	err = build_scmdlist(token_list, scmds_list);
	if (err != 1)
		return (err);
	err = find_redir(scmds_list);
	if (err != 1)
		return (err);
	err = find_cmdname(scmds_list);
	return (err);
}

// void	parser(t_token **token_list, t_scmd **scmds_list)
// {
// 	t_token	*aux;
	
// 	aux = *token_list;
// 	while (aux)
// 	{
// 		if (aux->type == PIPE)
// 			aux = aux->next;
// 		else if (aux->type == IN_REDIR || aux->type == OUT_REDIR)
// 			aux = handle_redir();
// 		else if (aux->type == WORD || aux->type == QUOTED_WORD)
// 			aux = handle_cmds();
// 	}
// }

// void	parse(t_token *token, t_scmd **scmds_list)
// {
// 	t_scmd	*simple_cmd;
// 	t_token	*aux;

// 	simple_cmd = NULL;
// 	while (token)
// 	{
// 		if (token->type == PIPE)
// 			token = token->next;
// 		else
// 		{
// 			simple_cmd = ms_lstnew_cmd(token->content);
// 			ms_lstadd_back(scmds_list, simple_cmd);
// 			token = token->next;
// 			aux = token;
// 			while (aux->type != PIPE || aux->type != IN_REDIR ||
// 			aux->type != OUT_REDIR || aux->type != HEREDOC ||
// 			aux->type != APPEND)
// 			{
// 				simple_cmd->word_count++;
// 				aux = aux->next;
// 			}
// 			if (simple_cmd->word_count != 0)
// 			{
// 				simple_cmd->cmd_words = malloc(sizeof(char *) * (simple_cmd->word_count + 1));
// 				if (simple_cmd->cmd_words == NULL)
// 					return (NULL);
// 				simple_cmd->cmd_words[simple_cmd->word_count] = NULL;
// 				simple_cmd->word_count--;
// 				while (simple_cmd->word_count >= 0)
// 				{
// 					simple_cmd->cmd_words[simple_cmd->word_count] = ft_strdup(token->content);
// 					simple_cmd->word_count--;
// 					token = token->next;
// 				}
// 			}
// 		}
// 	}
// }