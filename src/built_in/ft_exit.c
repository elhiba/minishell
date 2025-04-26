/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/23 01:30:14 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// it now frees the env and prints exit
int	do_exit(t_data *data)
{
	free_token_list(&data->token_list);
	free_d_arr(data->env);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
