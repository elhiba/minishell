/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 09:07:08 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 16:38:38 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *str, char d)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == d)
			str++;
		if (*str != d && *str != '\0')
		{
			count++;
			while (*str != d && *str != '\0')
				str++;
		}
	}
	return (count);
}

static void	sus(char *str, char c, int *start, int *end)
{
	while (str[*start] && str[*start] == c)
		(*start)++;
	*end = *start;
	while (str[*end] && str[*end] != c)
		(*end)++;
}

static char	*malloki(char *src, int start, int end)
{
	char	*dest;

	dest = ft_collector(sizeof(char) * ((end - start) + 1), ALLOC);
	if (!dest)
		return (ft_collector(0, EXIT));
	ft_memcpy(dest, src + start, (end - start));
	dest[(end - start)] = '\0';
	return (dest);
}

static char	**ft_free(char **words, int index)
{
	while (index >= 0)
	{
		free(words[index]);
		index--;
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		end;
	char	**words;

	if (!s)
		return (NULL);
	i = 0;
	start = 0;
	words = ft_collector(sizeof(char *) * (count_words((char *)s, c) + 1), ALLOC);
	if (!words)
		return (ft_collector(0, EXIT));
	while (s[start])
	{
		sus((char *)s, c, &start, &end);
		if (s[start] == '\0')
			break ;
		words[i] = malloki((char *)s, start, end);
		if (!words[i])
			ft_free(words, i);
		i++;
		start = end;
	}
	words[i] = NULL;
	return (words);
}
