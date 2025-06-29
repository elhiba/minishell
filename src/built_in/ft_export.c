/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/29 22:44:25 by moel-hib         ###   ########.fr       */
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

void	add_to_env(char *arg, char ***env)
{
	char	**new_env;
	int		counter;
	int		index;

	index = 0;
	counter = 0;
	while ((*env)[counter])
		counter++;
	new_env = ft_collector(sizeof(char *) * (counter + 2), ALLOC);
	while ((*env)[index])
	{
		new_env[index] = (*env)[index];
		index++;
	}
	new_env[index] = ft_strdup(arg);
	*env = new_env;
}

void	export_filter(char *arg, char ***env)
{
	int	i;
	
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i])
		add_to_env(arg, env);
}

int	do_export(t_cmd *data)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = ++data->argv;

	while (ptr[i])
	{
		export_filter(ptr[i], &data->data->env);
		i++;
	}
	return (1);
}
