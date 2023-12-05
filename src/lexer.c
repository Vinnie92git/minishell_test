/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:11:27 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/05 10:26:41 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_words(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;

	token = ms_lstnew();
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end]))
		end++;
	token->content = ft_substr(input, i, end - i);
	ms_lstadd_back(token_list, token);
	free(token);
	return (end);
}

int	handle_operators(t_token **token_list, char *input, int i)
{
	t_token	*token;

	token = NULL;
	token = ms_lstnew();
	token->type = operator_type(input, i);
	if (token->type == HEREDOC || token->type == APPEND)
	{
		token->content = ft_substr(input, i, 2);
		i++;
	}
	else
		token->content = ft_substr(input, i, 1);
	i++;
	ms_lstadd_back(token_list, token);
	free(token);
	return (i);
}

int	handle_quotes(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;
	int		quote;

	token = NULL;
	token = ms_lstnew();
	end = i;
	quote = is_quote(input[i]);
	end++;
	while (input[end] && quote != 0)
	{
		if (quote == is_quote(input[end]))
			quote = 0;
		end++;
	}
	if (quote)
		panic(QUOTING_ERR, token_list, token);
	token->content = ft_substr(input, i, end - i);
	if (is_quote(i) == SINGLE_QUOTE)
		token->type = SQ_WORD;
	else
		token->type = DQ_WORD;
	ms_lstadd_back(token_list, token);
	free(token);
	return (end);
}

int	lexer(t_token **token_list, char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (is_space(input[i]))
			i++;
		else if (is_quote(input[i]))
			i = handle_quotes(token_list, input, i);
		else if (is_operator(input[i]))
			i = handle_operators(token_list, input, i);
		else
			i = handle_words(token_list, input, i);
		i++;
	}
	// ms_print_lst(*token_list);
	return (0);
}
