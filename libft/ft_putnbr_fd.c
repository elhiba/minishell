/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:06:44 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/10/26 14:56:26 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	long	digit_rep;

	num = n;
	digit_rep = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	else if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	while ((num / digit_rep) >= 10)
	{
		digit_rep *= 10;
	}
	while (digit_rep != 0)
	{
		ft_putchar_fd('0' + (num / digit_rep), fd);
		num = num % digit_rep;
		digit_rep /= 10;
	}
}
