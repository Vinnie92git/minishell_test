/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:58 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/12 21:53:57 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_close_fds(t_scmd **list)
{
	t_scmd	*aux;

	if (list != NULL)
	{
		aux = *list;
		while (aux)
		{
			if (aux->infile != -1)
				close(aux->infile);
			if (aux->heredoc)
				unlink(".heredoc");
			if (aux->outfile != -1)
				close(aux->outfile);
			aux = aux->next;
		}
	}
}

void	ms_print_cmdlst(t_scmd *sequence)
{
	t_token	*aux;
	int		i;
	
	while (sequence)
	{
		aux = sequence->wordlist;
		printf("--word sequence between pipes--\n");
		while (aux)
		{
			printf("%s\n", aux->content);
			aux = aux->next;
		}
		if (sequence->cmd_args)
		{
			printf("--command name--\n");
			printf("%s\n", sequence->cmd_name);
			i = 0;
			printf("--command name/arguments--\n");
			while (sequence->cmd_args[i])
				printf("%s\n", sequence->cmd_args[i++]);
		}
		sequence = sequence->next;
	}
}

t_scmd	*ms_cmdnew(void)
{
	t_scmd	*new;

	new = NULL;
	new = malloc(sizeof(t_scmd));
	if (new == NULL)
		return (NULL);
	new->infile = -1;
	new->outfile = -1;
	new->heredoc = 0;
	new->cmd_name = NULL;
	new->cmd_path = NULL;
	new->cmd_args = NULL;
	new->wordlist = NULL;
	new->next = NULL;
	return (new);
}

void	ms_cmdadd_back(t_scmd **list, t_scmd *new)
{
	t_scmd	*aux;

	aux = *list;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	else
	{
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
}

void	ms_cmdclear(t_scmd **list)
{
	t_scmd	*aux;

	if (list != NULL)
	{
		while (*list)
		{
			aux = (*list)->next;
			ms_lstclear(&(*list)->wordlist);
			free(*list);
			(*list) = aux;
		}
		*list = NULL;
	}
}
