/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:11 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/14 00:02:03 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_child(t_scmd *scmd, t_info *info, int upstream, int pipe_w)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
	{
		if (scmd->infile != -1)
		{
			dup2(scmd->infile, STDIN_FILENO);
			close(scmd->infile);
		}
		else if (upstream != -1)
		{
			dup2(upstream, STDIN_FILENO);
			close(upstream);
		}
		if (scmd->outfile != -1)
		{
			dup2(scmd->outfile, STDOUT_FILENO);
			close(scmd->outfile);
		}
		else if (pipe_w != -1)
		{
			dup2(pipe_w, STDOUT_FILENO);
			close(pipe_w);
		}
		return (execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy));
	}
	return (1);
}

int	single_child(t_scmd *scmd, t_info *info, int upstream)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
	{
		if (scmd->infile != -1)
		{
			dup2(scmd->infile, STDIN_FILENO);
			close(scmd->infile);
		}
		else if (upstream != -1)
		{
			dup2(upstream, STDIN_FILENO);
			close(upstream);
		}
		if (scmd->outfile != -1)
		{
			dup2(scmd->outfile, STDOUT_FILENO);
			close(scmd->outfile);
		}
		return (execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy));
	}
	return (1);
}

int	get_cmd(t_scmd *scmd, t_info *info)
{
	char	*aux;
	char	*command;
	int		i;

	i = 0;
	while (info->bin_paths[i])
	{
		aux = ft_strjoin(info->bin_paths[i], "/");
		command = ft_strjoin(aux, scmd->cmd_name);
		free(aux);
		if (access(command, F_OK & R_OK & X_OK) == 0)
		{
			scmd->cmd_path = command;
			printf("command %s is valid\n", scmd->cmd_name);
			return (1);
		}
		free(command);
		i++;
	}
	return (COMMAND_ERR);
}

int	check_path(t_scmd *scmd)
{
	if (scmd->cmd_name[0] == '.' || scmd->cmd_name[0] == '/')
	{							
		if (access(scmd->cmd_name, F_OK & R_OK & X_OK) == 0)
		{
			printf("command path %s is valid\n", scmd->cmd_name);
			return (1);
		}
		else
			return (COMMAND_ERR);
	}
	return (0);
}
