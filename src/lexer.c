/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:11:27 by vipalaci          #+#    #+#             */
/*   Updated: 2023/11/27 15:00:50 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_quotes(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;
	int		quote;

	token = NULL;
	token = ms_lstnew();
	end = i;
	quote = 1;
	while (input[end] && !is_quote(input[end]))
	{
		if (is_quote(input[end]))
			quote = 0;
		end++;
	}
	if (quote)
		panic(QUOTING_ERR, token_list, token);
	token->content = ft_substr(input, i, end - i);
	token->type = WORD;
	ms_lstadd_back(token_list, token);
	free(token);
	return (end);
}

void	lexer(t_token **token_list, char *input)
{
	int		i;
	
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (is_quote(input[i]))
			i = handle_quotes(token_list, input, i);
		else if (is_operator(input[i]))
			i = handle_operators(token_list, input, i);
		else
			i = handle_words(token_list, input, i);
	}
}

// {
// 	while (input[i] && !is_quote(input[i]) && !is_operator(input[i]))
// 		i++;
// 	end = i;
// }