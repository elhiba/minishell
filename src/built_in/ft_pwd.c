/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/13 16:07:08 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * we should use (getcwd) function!
 * */
int	do_pwd(void)
{
	char	cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		error_handler("getcwd");
	printf("%s\n", cwd);
	return (1);
}
