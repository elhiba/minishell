/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:39:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:09:38 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_handler(char *error_name, t_data *data)
{
	if (error_name)
		perror(error_name);
	(void)data;
	exit(EXIT_FAILURE);
}
