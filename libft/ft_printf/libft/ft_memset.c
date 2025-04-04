/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:18:04 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/10/23 23:36:33 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *string, int c, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = string;
	while (n--)
	{
		str[i] = c;
		i++;
	}
	return (string);
}
