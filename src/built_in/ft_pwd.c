/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/06 11:52:21 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * we should use (getcwd) function!
 * */
int	ft_pwd()
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		error_handler("getcwd");
	printf("%s", cwd);
	return (0);
}
