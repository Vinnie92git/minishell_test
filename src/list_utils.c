/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:57:51 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/03 14:52:10 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	ms_print_lst(t_token *token)
{
	while (token)
	{
		printf("token = -%s- type = -%d-\n", token->content, token->type);
		token = token->next;
	}
}

// t_scmd	*ms_lstnew_cmd(char *content)
// {
// 	t_scmd	*new;

// 	new = NULL;
// 	new = malloc(sizeof(t_scmd));
// 	if (new == NULL)
// 		return (NULL);
// 	new->cmd = ft_strdup(content);
// 	new->cmd_args = NULL;
// 	new->arg_count = 0;
// 	new->next = NULL;
// 	return (new);
// }

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
