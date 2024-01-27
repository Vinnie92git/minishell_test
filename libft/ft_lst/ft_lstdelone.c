/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:57:44 by vipalaci          #+#    #+#             */
/*   Updated: 2023/04/09 14:25:47 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_lst/ft_lst.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
int	main()
{
	t_list *lst;
	lst = (t_list *)malloc(sizeof(t_list));
	lst->content = "hola";
	lst->next = NULL;
	ft_lstdelone(lst, free);
	printf("%s", lst->content);
	return (0);
}*/
/*La función tiene como objetivo eliminar
un elemento específico de la lista enlazada.*/
