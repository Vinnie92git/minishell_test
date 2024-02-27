/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/27 14:00:42 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info info)
{
	int	err;

	err = lexer(&list, line);
	add_history(line);
	if (err != 1)
		panic(err, NULL, NULL);
	if (err == 1)
	{
		// ms_print_lst(list);
		err = parser(&list, &scmds, &info);
		if (err != 1)
			panic(err, NULL, NULL);
		// ms_print_cmdlst(scmds);
		err = executer(&scmds, &info);
		if (err != 1)
			panic(err, NULL, NULL);
	}
	free(line);
	ms_lstclear(&list);
	ms_close_fds(&scmds);
	ms_cmdclear(&scmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	char	*cmd_line;

	if (argc > 1 || ft_strncmp(argv[0], "./minishell", ft_strlen(argv[0])))
		return (printf("No smartass shenanigans, just the executable ;)\n"));
	token_list = NULL;
	scmds_list = NULL;
	cmd_line = NULL;
	info.env_cpy = copy_env(envp);
	while (1)
	{
		cmd_line = readline("minishell-1.0$ ");
		if (!cmd_line)
			exit(0);
		if (cmd_line[0])
		{
			cmd_line[ft_strlen(cmd_line)] = '\0';
			shell_operation(cmd_line, token_list, scmds_list, info);
		}
	}
	return (0);
}
