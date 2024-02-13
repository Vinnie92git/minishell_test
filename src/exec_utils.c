/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:11 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/13 01:01:14 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	create_child(t_scmd *scmd, t_info *info)
// {
// 	pid_t	pid;
// 	int		pipe_fd[2];

// 	if (pipe(pipe_fd) == -1)
// 		return (PIPE_ERR)
// 	pid = fork();
// 	if (pid == -1)
// 		return (FORK_ERR)
// 	if (pid == 0)
// 	{
// 		// child
// 		close(pipe_fd[0]);
// 		if (scmd->outfile != -1)
// 			dup2(scmd->outfile, 1);
// 		else
// 			dup2(pipe_fd[1], 1);
			
// 		// execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy);
// 	}
// 	else
// 	{
// 		// parent
// 		close(pipe_fd[1]);
// 	}
// }

int	single_child(t_scmd *scmd, t_info *info)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		return (FORK_ERR);
	if (pid == 0)
	{
		if (scmd->infile != -1)
			dup2(scmd->infile, 0);
		if (scmd->outfile != -1)
			dup2(scmd->outfile, 1);
		return (execve(scmd->cmd_path, scmd->cmd_args, info->env_cpy));
	}
	else
	{
		return (1);
	}
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
