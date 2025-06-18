/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:19:46 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 16:37:05 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long n)
{
	int	count;

	count = 0;
	if (n < 0)
		n *= -1;
	while (0 < n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static unsigned int	len_counter(long n, int len)
{
	len = 0;
	if (n < 0)
	{
		n *= -1;
		len = count_digits(n) + 1;
	}
	else if (n == 0)
		len = 1;
	else
		len = count_digits(n);
	return (len);
}

static void	tmjnina(int *sign, long *number, char *num)
{
	*sign = 1;
	*number *= -1;
	num[0] = '-';
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*num;
	long	number;

	number = (long)n;
	sign = 0;
	len = 0;
	len = len_counter(number, len);
	num = ft_collector(sizeof(char) * (len + 1), ALLOC);
	if (!num)
		return (ft_collector(0, EXIT));
	num[len] = '\0';
	if (number < 0)
		tmjnina(&sign, &number, num);
	while (sign < len)
	{
		num[len - 1] = (number % 10) + 48;
		number /= 10;
		len--;
	}
	return (num);
}
