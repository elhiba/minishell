/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:00:46 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/10/23 23:38:28 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	i = 0;
	j = 0;
	if (len_needle == 0)
		return ((char *)haystack);
	while (i < n && haystack[i])
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && needle[j] && (i + j) < n
			&& haystack[i + j])
		{
			j++;
			if (j == len_needle)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
