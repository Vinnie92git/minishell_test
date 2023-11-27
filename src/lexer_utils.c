/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:58:28 by vipalaci          #+#    #+#             */
/*   Updated: 2023/11/27 12:35:18 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
		return (TRUE);
	return (FALSE);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (TRUE);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (TRUE);
	return (FALSE);
}
