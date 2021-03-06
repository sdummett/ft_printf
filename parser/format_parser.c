/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:50:39 by sdummett          #+#    #+#             */
/*   Updated: 2021/07/09 15:04:18 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

/*
 *	width_parsing() stock the value of the field width in flag->width.
*/

static void	width_parsing(t_attribs *flag, char **fmt, va_list var, int *i)
{
	int	j;

	j = *i;
	if ((*fmt)[j] == '-')
	{
		flag->negative = -1;
		j++;
	}
	while ((*fmt)[j] == '0')
		j++;
	while ((*fmt)[j] == '-')
		j++;
	if ((*fmt)[j] == '*')
	{
		flag->width = va_arg(var, int);
		if (flag->negative == -1 && flag->width > 0)
			flag->width = flag->width * -1;
		j++;
	}
	else
		flag->width = ft_atoi(&(*fmt)[j]) * flag->negative;
	while (((*fmt)[j] >= '0' && (*fmt)[j] <= '9') || \
			(*fmt)[j] == '-')
		j++;
	*i = j;
}

/*
 *	fmt_parser() will parse the format string and call the right in order
 *	to save the value.
*/

t_attribs	*fmt_parser(char **fmt, va_list var)
{
	int			i;
	t_attribs	*flag;

	flag = struct_init();
	i = 0;
	if ((*fmt)[i] == ' ')
		blank_parsing(flag, fmt, &i);
	if ((*fmt)[i] == '+')
		plus_parsing(flag, fmt, &i);
	if ((*fmt)[i] == '#')
		sharp_parsing(flag, fmt, &i);
	if ((*fmt)[i] == '0')
		zero_parsing(flag, fmt, var, &i);
	if ((*fmt)[i] == '+')
		plus_parsing(flag, fmt, &i);
	if (((*fmt)[i] >= '1' && (*fmt)[i] <= '9') || \
			(*fmt)[i] == '-' || (*fmt)[i] == '*')
		width_parsing(flag, fmt, var, &i);
	if ((*fmt)[i] == '.')
		dot_parsing(flag, fmt, var, &i);
	return (flag);
}
