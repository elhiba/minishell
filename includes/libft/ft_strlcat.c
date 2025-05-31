/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:48:43 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 16:24:23 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lens;
	size_t	lend;

	i = 0;
	lens = ft_strlen(src);
	if (!dst && size == 0)
		return (lens);
	lend = ft_strlen(dst);
	if ((lend) >= size)
		return (size + lens);
	while (src[i] && (lend + i) < size - 1)
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lens + lend);
}
