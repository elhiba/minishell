/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:54:41 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/11/23 00:39:58 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (check_format(&s[i] + 1) == 1)
				count += handle_format(s, args, &i);
			else
				count += ft_putchar(s[i]);
		}
		else
			count += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (count);
}

int	handle_format(const char *str, va_list args, int *i)
{
	t_flags	flags;

	flags = handle_flags(str, i);
	if (str[*i] == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (str[*i] == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (str[*i] == '%')
		return (ft_putchar('%'));
	else if (str[*i] == 'd' || str[*i] == 'i')
		return (ft_putnbr_flags(va_arg(args, int), flags));
	else if (str[*i] == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (str[*i] == 'x' || str[*i] == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), str[*i], flags));
	else if (str[*i] == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long)));
	return (1);
}

t_flags	handle_flags(const char *str, int *i)
{
	t_flags	flags;

	flags.hash = 0;
	flags.space = 0;
	flags.plus = 0;
	(*i)++;
	while (is_flag(str[*i]))
	{
		if (str[*i] == '+')
			flags.plus = 1;
		if (str[*i] == ' ')
			flags.space = 1;
		if (str[*i] == '#')
			flags.hash = 1;
		(*i)++;
	}
	return (flags);
}

int	check_format(const char *str)
{
	int	j;

	j = 0;
	while (str[j] && is_flag(str[j]))
		j++;
	if (!is_format(str[j]))
		return (0);
	return (1);
}
