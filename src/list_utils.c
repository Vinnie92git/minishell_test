/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:57:51 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/18 17:07:08 by vini             ###   ########.fr       */
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

void	ms_print_lst(t_token *token)
{
	while (token)
	{
		printf("token = -%s- type = -%d-\n", token->content, token->type);
		token = token->next;
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
