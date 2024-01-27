/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:45:54 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/27 18:55:30 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	panic(int err, t_token **list, t_token *token)
{
	if (err == QUOTING_ERR)
		printf("no closing quotes found\n");
	else if (err == READLINE_ERR)
		printf("readline error\n");
	else if (err == PARSE_ERR)
		printf("parsing error\n");
	if (list)
		ms_lstclear(list);
	if (token)
		free(token);
}
