/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:16:05 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/08 14:39:29 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			printf("comand %s is valid\n", scmd->cmd_name);
			return (1);
		}
		free(command);
		i++;
	}
	return (COMMAND_ERR);
}

int	check_cmd(t_scmd **scmds_list, t_info *info)
{
	t_scmd	*aux;
	int		err;
	
	aux = *scmds_list;
	err = 1;
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

	err = check_cmd(scmds_list, info);
	return (err);
}

// void executeCommands(SimpleCommand* commands) {
//     while (commands != NULL) {
//         pid_t pid = fork();

//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             execvp(commands->command, commands->command_arguments);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         } else {
//             waitpid(pid, NULL, 0);
//             commands = commands->next;
//         }
//     }
// }

