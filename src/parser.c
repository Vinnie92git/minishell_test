/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:07:20 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/02 23:19:28 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_cmdargs(t_scmd *simple_cmd, char *content)
{
	
}

void	parse(t_token *token, t_scmd **scmds_list)
{
	t_scmd	*simple_cmd;
	t_token	*aux;

	simple_cmd = NULL;
	while (token)
	{
		if (token->type == PIPE)
			token = token->next;
		else
		{
			simple_cmd = ms_lstnew_cmd(token->content);
			ms_lstadd_back(scmds_list, simple_cmd);
			token = token->next;
		}
	}
}
