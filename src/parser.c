/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/14 10:53:11 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_cmds(t_scmd **scmds_list)
{
	t_scmd	*aux;
	int		err;

	aux = *scmds_list;
	err = 1;
	while (aux)
	{
		err = build_cmd(aux);
		if (err != 1)
			return (err);
		aux = aux->next;
	}
	return (err);
}

int	handle_redir(t_scmd **scmds_list)
{
	t_scmd	*aux;
	int		err;

	aux = *scmds_list;
	err = 1;
	while (aux)
	{
		err = check_files(aux);
		if (err != 1)
			return (err);
		aux = aux->next;
	}
	return (err);
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
			aux->type = FILENAME;
		}
		aux = aux->next;
	}
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
	err = handle_redir(scmds_list);
	if (err != 1)
		return (err);
	err = find_cmds(scmds_list);
	return (err);
}
