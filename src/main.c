/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2023/11/27 12:41:26 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
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
		lexer(&token_list, cmd_line);
		ms_print_lst(token_list);
		ms_lstclear(token_list);
	}
	free(cmd_line);
	return (0);
}
