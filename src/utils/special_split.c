/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:12:11 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/21 16:20:32 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*
	if (s[i] == '\0')
		break ;
*/
static char	**alloc_words(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	w_len;
	int	is_squote;
	int	is_dquote;

	(1) && (i = 0, j = 0);
	(1) && (is_dquote = 0, is_squote = 0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		w_len = 0;
		while (s[i])
		{
			check_quotes((char *)s, i, &is_dquote, &is_squote);
			(1) && (i++, w_len++);
			if (s[i] == c && !is_dquote && !is_squote)
				break ;
		}
		arr[j] = ft_collector(w_len + 1, ALLOC);
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
	arr = ft_collector(sizeof(char *) * (wrd_count + 1), ALLOC);
	if (!arr)
		return (ft_collector(0, EXIT));
	arr = alloc_words(arr, s, c);
	return (arr);
}

int	exist(char *ptr, char ***env)
{
	char	*trim;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ptr[j] && ptr[j] != '=')
		j++;
	trim = ft_strtrim(ptr, j);
	if (ptr[j])
	{
		while ((*env)[i])
		{
			if (ft_strncmp(trim, (*env)[i], ft_strlen(trim)) == 0)
			{
				(*env)[i] = ft_strdup(ptr);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
