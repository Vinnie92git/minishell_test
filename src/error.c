/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:45:54 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/22 10:43:50 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	panic(int err, t_token **list, t_token *token)
{
	if (err == QUOTING_ERR)
		printf("no closing quotes found\n");
	else if (err == READLINE_ERR)
		printf("readline error\n");
	if (list)
		ms_lstclear(list);
	if (token)
		free(token);
}
