/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:31:42 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/15 14:51:02 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*quoted_dsign(char *input, int i, int end, char **env)
{
	char	*str;
	int		j;

	j = 0;
	str = ft_substr(input, i, end - i);
	if (!ft_strchr(str, '$'))
		return (str);
	
}
