/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:15:01 by vini              #+#    #+#             */
/*   Updated: 2024/02/20 13:29:15 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quoted_dsign(char *str, char **env, int i)
{
	int	quote;

	quote = is_quote(str[i]);
	while (str[i++] && quote != 0)
	{
		if (quote == is_quote(str[i]))
			quote = 0;
		else if (str[i] == '$')
			str = expand_dsign(str, env);
	}
	return (str);
}

int	closing_quote(char *str, int i)
{
	int	quote;

	quote = is_quote(str[i]);
	while (str[i++] && quote != 0)
		if (quote == is_quote(str[i]))
			quote = 0;
	return (i);
}
