/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 17:21:59 by sdummett          #+#    #+#             */
/*   Updated: 2021/06/26 05:21:01 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

/////////// TEMP /////////// 

#include <stdio.h>

//////////////////////////// 

/////////// MYF FUNC ///////

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(long long int nb);
void	ft_puthex_low(long int nb);
void	ft_puthex_up(long int nb);

//////////////////////////// 

#include "libft/libft.h"
#include <stdarg.h>

#endif
