/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/13 21:15:22 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_env(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while(envp[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) + (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while(envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_cpy[i] = '\0';
	return (env_cpy);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	char	*cmd_line;
	char	**env_cpy;

	token_list = NULL;
	cmd_line = NULL;
	env_cpy = get_env(envp);
	while (1)
	{
		cmd_line = readline("minishell-0.2$ ");
		if (!cmd_line)
			panic(READLINE_ERR, NULL, NULL);
		cmd_line[ft_strlen(cmd_line)] = '\0';
		lexer(&token_list, cmd_line);
		add_history(cmd_line);
		// ms_check_lst(token_list, PIPE);
		// ms_print_lst(token_list);
		free(cmd_line);
		ms_lstclear(&token_list);
	}
	return (0);
}
