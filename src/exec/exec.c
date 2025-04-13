/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/12 21:52:39 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execution(char **arg, char *env)
{
	(void)env;
	if (execve("/bin/ls", arg, NULL) == -1)
		error_handler("execve");
}
