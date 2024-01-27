/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:47:15 by vinni             #+#    #+#             */
/*   Updated: 2023/04/10 20:42:06 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTHERS_H
# define FT_OTHERS_H

# include <unistd.h>
# include <stdlib.h>
# include "../ft_str/ft_str.h"

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
