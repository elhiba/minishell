/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:39:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/14 10:37:11 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * this is not a complete functions!
 *
 * 	
 * */
void	error_handler(char *error_name)
{
	if (error_name)
		perror(error_name);
	exit(EXIT_FAILURE);
}
