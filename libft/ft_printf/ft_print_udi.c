/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_udi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:13:46 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/11/23 00:35:38 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_flags(int n, t_flags flags)
{
	int	print_count;

	print_count = 0;
	if (n >= 0)
	{
		if (flags.plus == 1)
			print_count += ft_putchar('+');
		else if (flags.space == 1)
			print_count += ft_putchar(' ');
	}
	print_count += ft_putnbr(n);
	return (print_count);
}

int	ft_print_unsigned(unsigned int n)
{
	int	print_count;

	print_count = 0;
	if (n >= 10)
		print_count += ft_print_unsigned(n / 10);
	print_count += ft_putchar((n % 10) + '0');
	return (print_count);
}

int	ft_putnbr(int n)
{
	int		print_count;
	char	*num;

	num = ft_itoa(n);
	print_count = ft_putstr(num);
	free(num);
	return (print_count);
}
