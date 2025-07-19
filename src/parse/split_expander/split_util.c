/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:08:22 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 00:08:38 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	there_is_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

void	extract_word(char **buffer, t_token **head, t_token *save)
{
	char	*token;
	int		len;
	t_token	*tmp;

	len = 0;
	while ((*buffer)[len] != '\0' && !is_space((*buffer)[len]))
		len++;
	token = ft_strndup(*buffer, len);
	*(buffer) += len;
	add_token_node(head, token);
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->is_squote = 1;
	if (save && save->is_ambiguous)
	{
		tmp->is_ambiguous = 1;
		tmp->ambiguous_name = save->ambiguous_name;
	}
	if (is_space(**buffer))
		tmp->is_space_next = 1;
}

int	all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}
