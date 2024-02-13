/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:16:05 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/13 23:58:48 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmds(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		pipe_fd[2];
	int		upstream;
	int		err;
	
	aux = *scmds_list;
	upstream = -1;
	while (aux)
	{
		if (pipe(pipe_fd) == -1)
			return (PIPE_ERR);
		if (!aux->next)
		{
			err = single_child(aux, info, upstream);
			if (err != 1)
				return (err);
		}
		else
		{
			err = exec_child(aux, info, upstream, pipe_fd[1]);
			if (err != 1)
				return (err);
		}
		close(pipe_fd[1]);
		upstream = pipe_fd[0];
		aux = aux->next;
	}
	while(wait(NULL) != -1 || errno != ECHILD);
	close(pipe_fd[0]);
	close(upstream);
	return (1);
}

int	check_cmds(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		err;
	
	aux = *scmds_list;
	while (aux)
	{
		err = check_path(aux);
		if (err == 1)
			aux->cmd_path = aux->cmd_name;
		else if (err == 0)
		{
			err = get_cmd(aux, info);
			if (err != 1)
				return (err);
		}
		else
			return (err);
		aux = aux->next;
	}
	return (err);
}

int	executer(t_scmd **scmds_list, t_info *info)
{
	int	err;

	err = check_cmds(scmds_list, info);
	if (err != 1)
		return (err);
	err = exec_cmds(scmds_list, info);
	return (err);
}
