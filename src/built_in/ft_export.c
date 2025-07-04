/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/03 23:58:42 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * ([X] mean works fine!)
 * export should make sure the allocated env is available:
 * first i would like to check if i already had this variable or not
 *	if (this variable exist)
 *		i should only updated it!
 *	else
 *		i should create new one and resort all variable (im not sure if needed to sort them!)
 *	if he add too mush vars like this example
 *	export SUS="djaja" ABMLO="ls -a" SNAKE="Im not lol!"
 *	-[X] i should loop on all this vars and add them to the env var!
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

int		is_export(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i])
	{
		if ((arg[i] >= 21 && arg[i] <= 47) || (arg[i] >= 58 && arg[i] <= 59)
			|| (arg[i] >= 63 && arg[i] <= 64) || (arg[i] >= 91 && arg[i] <= 94)
			|| arg[i] == 96 || (arg[i] >= 123 && arg[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}

void	export_filter(char *arg, char ***env)
{
	int	i;
	
	i = 0;
	if (is_export(arg))
	{
		if (arg[i])
			add_to_env(arg, env);
	}
	else
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 27);
	}
}

int		exist(char *ptr, char ***env)
{
	char	*trim;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ptr[j] && ptr[j] != '=')
		j++;
	trim = ft_strtrim(ptr, j);
	if (ptr[j])
	{
		while ((*env)[i])
		{
			if (ft_strncmp(trim, (*env)[i], ft_strlen(trim)) == 0)
			{
				(*env)[i] = ft_strdup(ptr);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int		do_export(t_cmd *data)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = ++data->argv;
	if (!ptr[i])
	{
		while (data->data->env[i])
		{
			write(1, "declare -x ", 11);
			write(1, data->data->env[i], ft_strlen(data->data->env[i]));
			write(1,"\n", 1);
			i++;
		}
	}
	i = 0;
	while (ptr[i])
	{
		if (exist(ptr[i], &data->data->env))
			;
		else
			export_filter(ptr[i], &data->data->env);
		i++;
	}
	return (1);
}
