/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/27 20:04:39 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	check_redir(t_scmd	*scmd)
// {
// 	int	i;

// 	i = 0;
// 	while (scmd->words[i])
// 	{
		
// 	}
// }

// int	find_redir(t_scmd **scmds_list)
// {
// 	t_scmd	*aux;
// 	int		i;

// 	aux = *scmds_list;
// 	while (aux)
// 	{
// 		check_redir(aux);
// 		aux = aux->next;
// 	}
// }

void	open_pipes(t_info *info)
{
	int	i;

	i = 0;
	if (info->pipe_nbr > 0)
		info->pipes = malloc(sizeof(int *) * pipe_nbr)
	if (!info->pipes)
	{
		//error;
		return ;
	}
	while (i < info->pipe_nbr)
	{
		if (pipe(info->pipes[i]) < 0)
			//error;
		i++;
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

int	build_scmdlist(t_token **token_list, t_scmd **scmds_list, t_info *info)
{
	t_token	*aux;
	int		cmd_nbr;
	
	aux = *token_list;
	cmd_nbr = 0;
	if (aux->type == PIPE)
		return (PARSE_ERR);
	while (aux)
	{
		if (aux->type == PIPE)
		{
			aux = aux->next;
			if (!aux)
				return (PARSE_ERR);
			if (aux->type == PIPE)
				return (PARSE_ERR);
		}
		aux = create_scmd(aux, scmds_list);
		cmd_nbr++;
	}
	info->pipe_nbr = cmd_nbr - 1;
	return (1);
}

int	parser(t_token **token_list, t_scmd **scmds_list, t_info *info)
{
	// t_redir	*redir_list;
	int	err;

	err = build_scmdlist(token_list, scmds_list, info);
	if (err != 1)
		ms_cmdclear(scmds_list);
	// err = open_pipes(info);
	// err = handle_redir(scmds_list);
	// err = find_cmdname(scmds_list);
	return (err);
}
