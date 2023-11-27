/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:11:27 by vipalaci          #+#    #+#             */
/*   Updated: 2023/11/27 14:35:13 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quotes(t_token *token_list, char *input, int i)
{
	t_token	*token;
	int		end;
	int		quote;

	token = NULL;
	token = ms_lstnew();
	end = i;
	quote = 1;
	while
	
	token->content = ft_substr(input, i, end - i);
	ms_lstadd_back(&token_list, token);
}

void	lexer(t_token *token_list, char *input)
{
	int		i;
	
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (is_quote(input[i]))
			handle_quotes(token_list, input, i);
		else if (is_operator(input[i]))
			handle_operators(token_list, input, i);
		else
			handle_words(token_list, input, i);
		i++;
	}
}

// {
// 	while (input[i] && !is_quote(input[i]) && !is_operator(input[i]))
// 		i++;
// 	end = i;
// }