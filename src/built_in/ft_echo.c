/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/07 18:57:33 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
 * i think echo need only printf? isn't it?
 */
int	do_echo(char *flag, char *input)
{
	(void)flag;
	if (printf("%s\n", input))
		return (0);
	return (1);
}
