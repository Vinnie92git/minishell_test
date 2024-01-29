/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/29 13:55:58 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (aux)
	{
		if (aux->type == PIPE)
			aux = aux->next;
		aux = create_scmd(aux, scmds_list);
		cmd_nbr++;
	}
	info->pipe_nbr = cmd_nbr - 1;
	return (1);
}

int	parser(t_token **token_list, t_scmd **scmds_list, t_info *info)
{
	int	err;

	info->path = get_path(info->env_cpy);
	info->bin_paths = ft_split(info->path, ':');
	err = check_syntax(token_list);
	if (err != 1)
		return (err);
	err = build_scmdlist(token_list, scmds_list, info);
	if (err != 1)
		ms_cmdclear(scmds_list);
	// err = open_pipes(info);
	// err = handle_redir(scmds_list);
	// err = find_cmdname(scmds_list);
	return (err);
}
