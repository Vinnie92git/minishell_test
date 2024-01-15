/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/15 14:47:54 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*create_cmd(t_token *token, t_scmd **scmds_list)
{
	t_scmd	*simple_cmd;
	t_token	*aux;
	int		i;

	simple_cmd = ms_cmdnew();
	aux = token;
	i = 0;
	while (aux->type != PIPE)
	{
		simple_cmd->arg_count++;
		aux = aux->next;
	}
	simple_cmd->args = malloc(sizeof(char *) * simple_cmd->arg_count);
	while (token->type != PIPE)
	{
		simple_cmd->args[i] = ft_strdup(token->content);
		i++;
		token = token->next;
	}
	simple_cmd->args[i] = '\0';
	ms_cmdadd_back(scmds_list, simple_cmd);
	return (token);
}

int	build_cmdlist(t_token **token_list, t_scmd **scmds_list)
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
		aux = create_cmd(aux, scmds_list);
	}
	return (1);
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
// 				simple_cmd->arg_count++;
// 				aux = aux->next;
// 			}
// 			if (simple_cmd->arg_count != 0)
// 			{
// 				simple_cmd->cmd_args = malloc(sizeof(char *) * (simple_cmd->arg_count + 1));
// 				if (simple_cmd->cmd_args == NULL)
// 					return (NULL);
// 				simple_cmd->cmd_args[simple_cmd->arg_count] = NULL;
// 				simple_cmd->arg_count--;
// 				while (simple_cmd->arg_count >= 0)
// 				{
// 					simple_cmd->cmd_args[simple_cmd->arg_count] = ft_strdup(token->content);
// 					simple_cmd->arg_count--;
// 					token = token->next;
// 				}
// 			}
// 		}
// 	}
// }