/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/30 15:02:51 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * we should use (getcwd) function!
 * */
int	do_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", ft_getenv("PWD", data));
	else
		printf("%s\n", cwd);
	data->last_exit_code = 0;
	return (1);
}
