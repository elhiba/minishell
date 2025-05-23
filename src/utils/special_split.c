/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:12:11 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/11 19:13:59 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int	is_squote;
	int	is_dquote;

	count = 0;
	i = 0;
	is_dquote = 0;
	is_squote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !is_dquote && !is_squote)
			count++;
		while (s[i] && s[i] != c)
		{
			check_quotes((char *)s, i, &is_dquote, &is_squote);
			i++;
		}
	}
	return (count);
}

static void	copy_word(char *arr, char const *s, int start, char c)
{
	int	i;
	int	is_dquote;
	int	is_squote;

	i = 0;
	is_dquote = 0;
	is_squote = 0;
	while (s[start] == ' ')
		start++;
	while (s[start])
	{
		check_quotes((char *)s, start, &is_dquote, &is_squote);
		arr[i] = s[start];
		start++;
		i++;
		if (s[start] == c && !is_dquote && !is_squote)
			break ;
	}
	arr[i] = '\0';
}

static char	**alloc_words(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	w_len;
	int	is_squote;
	int	is_dquote;

	i = 0;
	j = 0;
	is_dquote = 0;
	is_squote = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		w_len = 0;
		while (s[i])
		{
			check_quotes((char *)s, i, &is_dquote, &is_squote);
			i++;
			w_len++;
			if (s[i] == c && !is_dquote && !is_squote)
				break ;
		}
		arr[j] = malloc(w_len + 1);
		if (!arr[j])
			return (free_array(arr));
		copy_word(arr[j++], s, i - w_len, c);
	}
	arr[j] = NULL;
	return (arr);
}

char	**special_split(char const *s, char c)
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
