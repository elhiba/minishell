/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:03:25 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/22 11:16:56 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*src;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		src = (char *)malloc(sizeof(char) * 1);
		if (!src)
			return (NULL);
		src[0] = '\0';
		return (src);
	}
	if (len > s_len - start)
		len = s_len - start;
	src = (char *)malloc(sizeof(char) * (len + 1));
	if (!src)
		return (NULL);
	ft_strlcpy(src, s + start, len + 1);
	return (src);
}
