/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:19:05 by slasfar           #+#    #+#             */
/*   Updated: 2025/05/31 16:40:34 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_collector((ft_strlen(s1) + n + 1) * sizeof(char), ALLOC);
	if (!str)
		return (ft_collector(0, EXIT));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && j < n)
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}
