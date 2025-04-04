/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:27:41 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/10/30 18:21:50 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	copy_word(char *arr, char const *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start] && s[start] != c)
	{
		arr[i] = s[start];
		start++;
		i++;
	}
	arr[i] = '\0';
}

static char	**alloc_words(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	w_len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		w_len = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			w_len++;
		}
		arr[j] = malloc(w_len + 1);
		if (!arr[j])
			return (free_array(arr));
		copy_word(arr[j++], s, i - w_len, c);
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wrd_count;

	if (!s)
		return (NULL);
	wrd_count = count_words(s, c);
	arr = malloc(sizeof(char *) * (wrd_count + 1));
	if (!arr)
		return (NULL);
	arr = alloc_words(arr, s, c);
	return (arr);
}
