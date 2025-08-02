/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:43:13 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * This is probably a complete function! Still no updates (looks fine)
 */

int	do_env(t_cmd *data)
{
	t_export	*env;
	int			i;

	i = 0;
	sort(&data->data->env);
	while (data->data->env[i])
	{
		parse_export(&env, data->data->env[i]);
		if (env->is_equal)
		{
			write(1, ft_strjoin(data->data->env[i], "\n"),
				ft_strlen(data->data->env[i]) + 1);
		}
		i++;
	}
	data->data->last_exit_code = 0;
	return (1);
}
