/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/28 21:04:03 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * export should make sure the allocated env is available:
 * first i would like to check if i already had this variable or not
 *	if (this variable exist)
 *		i should only updated it!
 *	else
 *		i should create new one and resort all variable (im not sure if needed to sort them!)
 *	if he add too mush vars like this example
 *	export SUS="djaja" ABMLO="ls -a" SNAKE="Im not lol!"
 *	i should loop on all this vars and add them to the env var!
 * */

int	do_export(t_cmd *data)
{
	
	return (1);
}
