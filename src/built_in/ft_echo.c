/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/09 12:52:38 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * i think echo need only printf? isn't it?
 */
int	do_echo(t_input *input)
{
	if (ft_strcmp(input->flags, "-n") == 0)
		printf("%s", input->args);
	else if (input->args)
		printf("%s\n", input->args);
	else if ((!input->flags || !input->args))
		printf("\n");
	return (0);
}
