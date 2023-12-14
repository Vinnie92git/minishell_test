/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:11:27 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/14 14:46:58 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_dsign(t_token **token_list, char *input, int i, char **env)
{
	t_token	*token;
	char	*var;
	int		end;

	token = ms_lstnew();
	// if (input[i + 1] == '?')
	// {
	// 	get_signal();
	// 	return (i + 2);
	// }
	i++;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	var = ft_substr(input, i, end - i);
	token->content = find_var(var, env);
	ms_lstadd_back(token_list, token);
	return (end);
}

int	handle_words(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;

	token = ms_lstnew();
	token->type = WORD;
	end = i;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quote(input[end]) && !is_dsign(input[end]))
		end++;
	token->content = ft_substr(input, i, end - i);
	ms_lstadd_back(token_list, token);
	return (end);
}

int	handle_operators(t_token **token_list, char *input, int i)
{
	t_token	*token;

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
	return (i);
}

int	handle_quotes(t_token **token_list, char *input, int i)
{
	t_token	*token;
	int		end;
	int		quote;

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
	return (end);
}

int	lexer(t_token **token_list, char *input, char **env)
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
		else if (is_dsign(input[i]))
			i = handle_dsign(token_list, input, i, env);
		else
			i = handle_words(token_list, input, i);
	}
	// ms_print_lst(*token_list);
	return (0);
}
