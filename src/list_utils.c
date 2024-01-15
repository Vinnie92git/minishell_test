/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:57:51 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/15 13:57:05 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

t_token	*ms_lstnew(void)
{
	t_token	*new;

	new = NULL;
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->type = INIT_INT;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

void	ms_lstadd_back(t_token **list, t_token *new)
{
	t_token	*aux;

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

void	ms_lstclear(t_token **list)
{
	t_token	*aux;

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
