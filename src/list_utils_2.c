/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:41:58 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/17 10:46:02 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ms_print_cmdlst(t_scmd *sequence)
{
	int	i;
	
	while (sequence)
	{
		i = 0;
		printf("--word sequence between pipes--\n");
		while (sequence->args[i])
		{
			printf("%s\n", sequence->args[i]);
			i++;
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
	new->arg_count = 0;
	new->args = NULL;
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
			free(*list);
			(*list) = aux;
		}
		*list = NULL;
	}
}
