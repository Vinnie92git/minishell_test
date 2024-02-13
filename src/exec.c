/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:16:05 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/13 15:33:10 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_cmds(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		err;
	
	aux = *scmds_list;
	if (info->pipe_nbr == 0)
	{
		err = single_child(aux, info);
		if (err != 1)
			return (err);
	}
	else
	{
		while (aux)
		{
			if (!aux->next)
				last_command();
			else
			{
				err = create_child(aux, info);
				if (err != 1)
					return (err);
			}
			aux = aux->next;
		}
	}
	while(wait(NULL) != -1 || errno != ECHILD);
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
