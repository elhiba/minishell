/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:23:14 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/30 13:29:09 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin3(const char *str1, const char *middle, const char *str2)
{
	char	*tmp;
	char	*full_result;

	tmp = ft_strjoin(str1, middle);
	full_result = ft_strjoin(tmp, str2);
	return (full_result);
}

char	*ft_strtrim(char *str, int limit)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_collector(sizeof(char) * (limit + 2), ALLOC);
	while (i <= limit)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

int		ft_arglen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

//void	free_token_list(t_token **head)
//{
//	t_token	*tmp;
//	t_token	*next;
//
//	if (!head || !*head)
//		return ;
//	tmp = *head;
//	while (tmp)
//	{
//		next = tmp->next;
//		if (tmp->arg)
//			free(tmp->arg);
//		free(tmp);
//		tmp = next;
//	}
//	*head = NULL;
//}

//void	free_d_arr(char **arr)
//{
//	char	**ptr;
//	int		i;
//
//	ptr = arr;
//	i = 0;
//	while (arr[i])
//	{
//		free(ptr[i]);
//		i++;
//	}
//	free(ptr);
//}

char	**ft_splits(char *arg, char *delimits)
{
	int		i;
	int		len;
	char	**args;

	i = 0;
	len = ft_strlen(delimits);
	while (i < len)
	{
		args = ft_split(arg, delimits[i]);
		if (!args)
			break ;
		i++;
	}
	return (args);
}
