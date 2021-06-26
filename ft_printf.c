/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 09:49:47 by sdummett          #+#    #+#             */
/*   Updated: 2021/06/26 19:19:56 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_format(char **format, va_list var) //envoyer la va_list
{
//	int i;

//	i = 0;
	while (**format != '\0')
	{
		if (**format == '%')
		{
			ft_putpercent();
			(*format)++;
			return ;
		}
		else if (**format == 'c')
		{
			ft_putchar(va_arg(var, int));
			(*format)++;
			return ;
		}
		else if (**format == 's')
		{
			ft_putstr(va_arg(var, char *));
			(*format)++;
			return ;
		}
		else if (**format == 'p')
		{
			ft_putaddr(va_arg(var, void *));
			(*format)++;
			return ;
		}
		else if (**format == 'd' || **format == 'i')
		{
			ft_putnbr(va_arg(var, int));
			(*format)++;
			return ;
		}
		else if (**format == 'u')
		{
			ft_putnbr(va_arg(var, unsigned int));
			(*format)++;
			return ;
		}
		else if (**format == 'x')
		{
			ft_puthex_low(va_arg(var, long int));
			(*format)++;
			return ;
		}
		else if (**format == 'X')
		{
			ft_puthex_up(va_arg(var, long int));
			(*format)++;
			return ;
		}
	}
}

int ft_printf(const char *format, ...)
{
//	int	i;
	va_list	vars;
	va_start(vars, format);
	
//	i = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			check_format((char **)&format, vars);
		}
		else
		{
			ft_putchar(*format);
			format++;
		}
	}
	va_end(vars);
	return (42);
}

