/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:56:56 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/10/26 14:57:31 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	char	*arr;
	int		len;

	num = n;
	len = int_len(num);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	len--;
	if (num < 0)
	{
		arr[0] = '-';
		num = -num;
	}
	if (num == 0)
		arr[0] = '0';
	while (num > 0)
	{
		arr[len] = num % 10 + '0';
		num /= 10;
		len--;
	}
	return (arr);
}
