/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:39:07 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/20 12:22:48 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * this is not a complete functions!
 *
 * 	//free list in error and improve othe stuff
 * */
void	error_handler(char *error_name, t_data *data)
{
	if (error_name)
		perror(error_name);
	if (data)
	{
		free_token_list(&data->token_list);
		free_d_arr(data->env);
	}
	exit(EXIT_FAILURE);
}
