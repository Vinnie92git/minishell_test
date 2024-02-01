/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:28:24 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/01 14:27:20 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_files(t_scmd *scmd)
{
	t_token	*aux;

	aux = scmd->wordlist;
	while (aux)
	{
		if (aux->type == IN_REDIR)
		{
			aux = aux->next;
			scmd->infile = open(aux->content, O_RDONLY);
			if (scmd->infile < 0)
				return (INFILE_ERR);
			printf("file %s opened for reading\n", aux->content);
		}
		aux = aux->next;
	}
	return (1);
}