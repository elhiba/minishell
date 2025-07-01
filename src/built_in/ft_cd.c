/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/01 22:17:29 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * We will try to make it performant handling more stuff like [cd - and updating the old pwd]
 * */

int	do_cd(t_cmd *data)
{
	char	*path;

	path = *(++data->argv);
	if (data->argv[1])
	{
		write(2, "minishell: too many arguments\n", 31);
		return (2);
	}
	if (chdir(path) == -1)
		perror(ft_strjoin("minishell: cd: ", path));
	return (1);
}
