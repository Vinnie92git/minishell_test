/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 20:40:48 by vini              #+#    #+#             */
/*   Updated: 2024/02/14 14:22:48 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	store_cmdargs(t_scmd *scmd)
{
	t_token	*aux;
	int		i;

	aux = scmd->wordlist;
	i = 0;
	while (aux)
	{
		if (aux->type == WORD || aux->type == QUOTED_WORD)
		{
			scmd->cmd_args[i] = ft_strdup(aux->content);
			i++;
		}
		aux = aux->next;
	}
	scmd->cmd_args[i] = 0;
	if (scmd->cmd_args[0])
		scmd->cmd_name = ft_strdup(scmd->cmd_args[0]);
}

int	build_cmd(t_scmd *scmd)
{
	t_token	*aux;
	int		argcount;

	aux = scmd->wordlist;
	argcount = 0;
	while (aux)
	{
		if (aux->type == WORD || aux->type == QUOTED_WORD)
			argcount++;
		aux = aux->next;
	}
	scmd->cmd_args = malloc(sizeof(char *) * (argcount + 1));
	if (scmd->cmd_args == NULL)
		return (MALLOC_ERR);
	store_cmdargs(scmd);
	return (1);
}
