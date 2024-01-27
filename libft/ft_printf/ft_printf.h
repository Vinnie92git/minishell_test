/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinni <vinni@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:42:01 by vinni             #+#    #+#             */
/*   Updated: 2023/04/10 20:37:52 by vinni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include "../ft_put/ft_put.h"

int		ft_printf(const char *str, ...);
int		ft_printstr(char *str);
int		ft_printptr(unsigned long long ptr);
int		ft_printnbr(int nbr);
int		ft_printuint(unsigned int nbr);
int		ft_printhex(unsigned int nbr, const char format);

#endif
