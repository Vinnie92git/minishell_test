/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/05 13:29:58 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_token	*token_list;
	char	*cmd_line;

	token_list = NULL;
	cmd_line = NULL;
	while (1)
	{
		cmd_line = readline("minishell-0.1$ ");
		if (cmd_line == NULL)
		{
			printf("readline error\n");
			exit (1);
		}
		cmd_line[ft_strlen(cmd_line)] = '\0';
		lexer(&token_list, cmd_line);
		add_history(cmd_line);
		printf("command line = %s\n", cmd_line);
	}
	return (0);
}
