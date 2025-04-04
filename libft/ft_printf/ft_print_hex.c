/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:25:37 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/11/23 00:34:33 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int n, char format, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.hash && n != 0)
	{
		if (format == 'x')
			count += ft_putstr("0x");
		else
			count += ft_putstr("0X");
	}
	count += ft_print_hex_recursive(n, format);
	return (count);
}

int	ft_print_hex_recursive(unsigned int n, char format)
{
	int		count;
	char	*hex;

	count = 0;
	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_print_hex_recursive(n / 16, format);
	count += ft_putchar(hex[n % 16]);
	return (count);
}

int	is_format(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || \
			c == 'i' || c == 'u' || c == 'x' || c == 'X' || \
			c == '%');
}

int	is_flag(char c)
{
	return (c == '+' || c == ' ' || c == '#');
}
