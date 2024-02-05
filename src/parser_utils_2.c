/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:28:24 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/05 22:41:02 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	open_heredoc(t_scmd *scmd, t_token *token)
// {
	
// }

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
	int		err;

	aux = scmd->wordlist;
	err = 1;
	while (aux)
	{
		if (aux->type == IN_REDIR)
			err = open_infile(scmd, aux->next);
		// else if (aux->type == HEREDOC)
		// 	err = open_heredoc(scmd, aux->next);
		else if (aux->type == OUT_REDIR)
			err = open_outfile(scmd, aux->next);
		else if (aux->type == APPEND)
			err = open_append(scmd, aux->next);
		if (err != 1)
			return (err);
		aux = aux->next;
	}
	return (err);
}