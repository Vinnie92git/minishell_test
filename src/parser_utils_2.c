/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:28:24 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/05 22:25:24 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_append(t_scmd *scmd, t_token *token)
{
	scmd->outfile = open(token->content, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (scmd->outfile < 0)
		return (OUTFILE_ERR);
	printf("file %s opened/created for writing/appending\n", token->content);
	return (1);
}

int	open_outfile(t_scmd *scmd, t_token *token)
{
	scmd->outfile = open(token->content, O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (scmd->outfile < 0)
		return (OUTFILE_ERR);
	printf("file %s opened/created for writing\n", token->content);
	return (1);
}

int	open_infile(t_scmd *scmd, t_token *token)
{
	scmd->infile = open(token->content, O_RDONLY, 0644);
	if (scmd->infile < 0)
		return (INFILE_ERR);
	printf("file %s opened for reading\n", token->content);
	return (1);
}

int	check_files(t_scmd *scmd)
{
	t_token	*aux;

	aux = scmd->wordlist;
	while (aux)
	{
		if (aux->type == IN_REDIR)
		{
			if (open_infile(scmd, aux->next) != 1)
				return (INFILE_ERR);
		}
		else if (aux->type == OUT_REDIR)
		{
			if (open_outfile(scmd, aux->next) != 1)
				return (OUTFILE_ERR);
		}
		else if (aux->type == APPEND)
		{
			if (open_append(scmd, aux->next) != 1)
				return (OUTFILE_ERR);
		}
		aux = aux->next;
	}
	return (1);
}