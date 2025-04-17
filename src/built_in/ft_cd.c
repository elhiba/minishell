/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/17 18:51:49 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * this is not a complete functions!
 */
int	do_cd(t_data *data)
{
	int		i;
	char	*cd_arg;
	t_token *current;

	if (data->token_list->next)
		cd_arg = data->token_list->next->arg;
	current = data->token_list;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	if (i == 1)
		chdir(getenv("HOME"));
	else if (i > 2)
		perror("cd: too many arguments");
	else if (cd_arg[0] == '-')
		chdir(getenv("OLDPWD"));
	else if (chdir(cd_arg) == -1)
		perror(cd_arg);
	return (1);
}
