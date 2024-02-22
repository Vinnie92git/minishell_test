/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/21 22:01:46 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	t_scmd	*scmds_list;
	t_info	info;
	char	*cmd_line;
	int		err;

	(void)argv;
	(void)argc;
	token_list = NULL;
	scmds_list = NULL;
	cmd_line = NULL;
	info.env_cpy = copy_env(envp);
	while (1)
	{
		cmd_line = readline("minishell-1.0$ ");
		if (!cmd_line)
			panic(READLINE_ERR, NULL, NULL);
		if (cmd_line[0])
		{
			cmd_line[ft_strlen(cmd_line)] = '\0';
			err = lexer(&token_list, cmd_line);
			add_history(cmd_line);
			if (err != 1)
				panic(err, NULL, NULL);
			if (err == 1)
			{
				ms_print_lst(token_list);
				err = parser(&token_list, &scmds_list, &info);
				if (err != 1)
					panic(err, NULL, NULL);
				ms_print_cmdlst(scmds_list);
				err = executer(&scmds_list, &info);
				if (err != 1)
					panic(err, NULL, NULL);
			}
			free(cmd_line);
			ms_lstclear(&token_list);
			ms_close_fds(&scmds_list);
			ms_cmdclear(&scmds_list);
		}
	}
	return (0);
}
