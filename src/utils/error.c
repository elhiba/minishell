/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:39:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:55:54 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handler(char *error_name, t_data *data)
{
	(void)data;
	if (error_name)
		perror(error_name);
	exit(EXIT_FAILURE);
}
