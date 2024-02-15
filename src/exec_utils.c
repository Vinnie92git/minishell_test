/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:11 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/16 00:37:46 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

int	exec_child(t_scmd *scmd, t_info *info, int upstream, int pipe_w, int pipe_r)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
	{
		close(pipe_r);
		if (scmd->infile != -1)
			ft_dup(scmd->infile, STDIN_FILENO);
		else if (upstream != -1)
			ft_dup(upstream, STDIN_FILENO);
		if (scmd->outfile != -1)
			ft_dup(scmd->outfile, STDOUT_FILENO);
		else if (pipe_w != -1)
			ft_dup(pipe_w, STDOUT_FILENO);
		if (!scmd->cmd_path)
			exit(127);
		return (execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy));
	}
	close(pipe_w);
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
			ft_dup(scmd->infile, STDIN_FILENO);
		else if (upstream != -1)
			ft_dup(upstream, STDIN_FILENO);
		if (scmd->outfile != -1)
			ft_dup(scmd->outfile, STDOUT_FILENO);
		if (!scmd->cmd_path)
			exit(127);
		return (execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy));
	}
	close(upstream);
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
