/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdummett <sdummett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 02:19:32 by sdummett          #+#    #+#             */
/*   Updated: 2021/07/05 19:38:31 by sdummett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_printf.h"

static t_flag_attribs	*integer_parser(char **format, va_list var)
{
	int				i;
	int				neg;
	t_flag_attribs	*flag;

	flag = struct_initializer();
	i = 0;
	neg = 1;
	if ((*format)[i] == '0')
	{
		i++;
		if ((*format)[i] == '*')
			flag->padding = va_arg(var, int);
		else
			flag->padding = ft_atoi(&(*format)[i]);
		while ((*format)[i] >= '0' && (*format)[i] <= '9')
			i++;
	}
	if (((*format)[i] >= '1' && (*format)[i] <= '9') || \
			(*format)[i] == '-' || (*format)[i] == '*')
	{
		if ((*format)[i] == '-')
		{
			neg = -1;
			i++;
		}
		if ((*format)[i] == '*')
		{
			flag->width = va_arg(var, int);
			i++;
		}
		else
			flag->width = ft_atoi(&(*format)[i]);
		if (flag->width > 0)
			flag->width = flag->width * neg;
		while (((*format)[i] >= '0' && (*format)[i] <= '9') || \
				(*format)[i] == '-')
			i++;
	}
	if ((*format)[i] == '.')
	{
		i++;
		if ((*format)[i] == '*')
			flag->precision = va_arg(var, int);
		else
			flag->precision = ft_atoi(&(*format)[i]);
		if (flag->precision == 0)
			flag->prec_is_dot = 1;
		while ((*format)[i] >= '0' && (*format)[i] <= '9')
			i++;
	}
	return (flag);
}

static char	*add_zero(char *str, int width_prec, int len, int flag)
{
	int		i;
	char	*new;

	if (str[0] == '-' && flag != 1)
	{
		if (width_prec < len)
			return (str);
	}
	else if (width_prec <= len)
		return (str);
	width_prec = width_prec - len;
	i = 0;
	if (str[i] == '-')
	{
		if (flag != 1)
			width_prec = width_prec + 1;
		new = (char *)malloc(sizeof(char) * len + width_prec + 1);
		new[i] = '-';
		str++;
		i++;
	}
	else
		new = (char *)malloc(sizeof(char) * len + width_prec + 1);
	while (width_prec != 0)
	{
		new[i] = '0';
		i++;
		width_prec--;
	}
	len = 0;
	while (str[len] != '\0')
	{
		new[i] = str[len];
		i++;
		len++;
	}
	new[i] = '\0';
	return (new);
}

static int	insert_spaces(char *str, int width)
{
	int	i;

	i = 0;
	while (width != 0)
	{
		str[i] = ' ';
		width--;
		i++;
	}
	return (i);
}

static char	*add_space(char *str, int width, int len)
{
	char	*new;
	int		i;

	i = 0;
	if (width < 0)
	{
		width = (width * -1) - len;
		if (width < 0)
			return (str);
		new = (char *)malloc(sizeof(char) + len + \
				width + 1);
		len = 0;
		while (str[len] != '\0')
		{
			new[i] = str[len];
			i++;
			len++;
		}
		insert_spaces(new + i, width);
		i = i + width ;
		new[i] = '\0';
		free(str);
		return (new);
	}
	width = width - len;
	if (width < 0)
		return (str);
	new = (char *)malloc(sizeof(char) + len + width + 1);
	i = insert_spaces(new, width);
	len = 0;
	while (str[len] != '\0')
	{
		new[i] = str[len];
		i++;
		len++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

static char	*create_str(char *str)
{
	int		len;
	char	*new;

	if (str == NULL)
		return (ft_strdup("(null)"));
	len = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * len + 1);
	len = 0;
	while (str[len] != '\0')
	{
		new[len] = str[len];
		len++;
	}
	new[len] = '\0';
	return (new);
}

static char	*resize_str(char *str, int precision, int len)
{
	char	*new;

	if (precision >= len)
		return (str);
	new = (char *)malloc(sizeof(char) * precision + 1);
	new[precision] = '\0';
	while (precision > 0)
	{
		precision--;
		new[precision] = str[precision];
	}
	free(str);
	return (new);
}

void	str_handler(char **format, va_list var, int *ptf_ret)
{
	t_flag_attribs	*flag;
	char			*str;
	int				len;

	len = 0;
	flag = integer_parser(format, var);
	str = create_str(va_arg(var, char *));
	if (flag->precision > 0 || flag->prec_is_dot == 1)
	{
		len = ft_strlen(str);
		str = resize_str(str, flag->precision, len);
	}
	if (flag->padding > 0 && flag->prec_is_dot == 1)
	{
		len = ft_strlen(str);
		str = add_zero(str, flag->padding, len, 1);
	}
	else if (flag->padding > 0 && flag->precision > 0)
		flag->width = flag->padding;
	if (flag->width != 0)
	{
		len = ft_strlen(str);
		str = add_space(str, flag->width, len);
	}
	while (**format != 's')
		(*format)++;
	(*format)++;
	len = ft_strlen(str);
	*ptf_ret = *ptf_ret + len;
	write(1, str, len);
	free(str);
	free(flag);
}
