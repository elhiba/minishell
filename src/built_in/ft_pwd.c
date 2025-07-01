/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/01 21:52:51 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Based on manual we can use `getcwd()` function or 
 * we can use `/proc/self/cwd` which can help us get our current directory!
 * */
int	do_pwd(t_cmd *data)
{
	char	path[PATH_MAX];

	(void)data;
	if (getcwd(path, sizeof(char [PATH_MAX])))
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);

	}
	else
		perror("getcwd");
	return (1);
}
