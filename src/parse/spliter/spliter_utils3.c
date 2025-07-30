/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:12:15 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/30 15:14:34 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	split_cmp_action(t_token **token, char *str, void **tx)
{
	*(int *)tx[1] = *(int *)tx[2];
	if (str[*(int *)tx[2]] == '\'' || str[*(int *)tx[2]] == '\"')
		add_token_node(token, quotes_handler(str, (int *)tx[2], (int *)tx[0]));
	else
	{
		while (str[*(int *)tx[2]] && str[*(int *)tx[2]] != ' ' && str[*(int *)tx[2]] != '\t'
			&& str[*(int *)tx[2]] != '\n' && str[*(int *)tx[2]] != '\v' && str[*(int *)tx[2]] != '\f'
			&& str[*(int *)tx[2]] != '\r' && str[*(int *)tx[2]] != '\'' && str[*(int *)tx[2]] != '\"'
			&& !operation_len(str + *(int *)tx[2]))
			(*(int *)tx[2])++;
		add_token_node(token, ft_substr(str, *(int *)tx[1], \
			*(int *)tx[2] - *(int *)tx[1]));
		*(int *)tx[0] = 1337;
	}
}

int	split_actions(t_token **token, char *str, void **tx)
{
	while (str[*(int *)tx[2]] == ' ' || str[*(int *)tx[2]] == '\t'
		|| str[*(int *)tx[2]] == '\n' || str[*(int *)tx[2]] == '\v'
		|| str[*(int *)tx[2]] == '\f' || str[*(int *)tx[2]] == '\r')
		(*(int *)tx[2])++;
	if (!str[*(int *)tx[2]])
		return (1);
	*(int *)tx[0] = operation_len(str + *(int *)tx[2]);
	if (*(int *)tx[0])
	{
		add_token_node(token, ft_substr(str, *(int *)tx[2], *(int *)tx[0]));
		*(int *)tx[2] += *(int *)tx[0];
	}
	else
		split_cmp_action(token, str, tx);
	return (0);
}

/*
	traff means TRAFFICKER
*/
void	ft_spliter(t_token **token, char *str, t_data *data)
{
	void	**traff;
	t_token	*ptr;
	int		op_len;
	int		start;
	int		i;

	(1) && (i = 0, traff = ft_collector(sizeof(void *) * 4, ALLOC));
	while (str[i])
	{
		(1) && (traff[0] = &op_len, traff[1] = &start, traff[2] = &i);
		if (split_actions(token, str, traff))
			break ;
		ptr = *token;
		while (ptr->next)
			ptr = ptr->next;
		if (op_len == 10)
			ptr->is_dquote = 1;
		else if (op_len == 11)
			ptr->is_squote = 1;
		else if (op_len == 1337)
			ptr->is_word = 1;
		space_checker(str, &ptr, i);
	}
	check_and_expand(token, data, data->env);
	set_ambiguous(*token, data);
}
