/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:49:57 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/02 23:54:52 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ms_check_lst(t_token *token, int type)
{
	while (token)
	{
		if (token->type == type)
			return (printf("requested type found\n"));
		token = token->next;
	}
	return (printf("requested type NOT found\n"));
}

char	**copy_env(char **envp)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env_cpy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_cpy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*token_list;
	// t_scmd	*scmds_list;
	char	*cmd_line;
	char	**env_cpy;
	int		err;

	(void)argv;
	(void)argc;
	token_list = NULL;
	cmd_line = NULL;
	env_cpy = copy_env(envp);
	while (1)
	{
		cmd_line = readline("minishell-0.2$ ");
		if (!cmd_line)
			panic(READLINE_ERR, NULL, NULL);
		cmd_line[ft_strlen(cmd_line)] = '\0';
		err = lexer(&token_list, cmd_line, env_cpy);
		if (err != 1)
			panic (err, NULL, NULL);
		add_history(cmd_line);
		// parser(token_list, &scmds_list);
		ms_print_lst(token_list);
		free(cmd_line);
		ms_lstclear(&token_list);
	}
	return (0);
}
