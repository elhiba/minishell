/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/30 13:55:45 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * ([X] mean works fine!)
 * export should make sure the allocated env is available:
 * first i would like to check if i already had this variable or not
 *	if (this variable exist)
  i should only updated it!
 *	else
  i should create new one and resort all variable (im not sure if 
  needed to sort them!)
 *	if he add too mush vars like this example
 *	export SUS="djaja" ABMLO="ls -a" SNAKE="Im not lol!"
 *	-[X] i should loop on all this vars and add them to the env var!
 * */

void	add_to_env(t_export *export, char ***env)
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
	if (*export->value)
		new_env[index] = ft_strjoin3(export->var, "=", export->value);
	else if (export->is_equal)
		new_env[index] = ft_strjoin(export->var, "=");
	else
		new_env[index] = ft_strdup(export->var);
	new_env[++index] = NULL;
	*env = new_env;
}

int	is_export(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if ((arg[i] >= 21 && arg[i] <= 47) || (arg[i] >= 58 && arg[i] <= 59)
			|| (arg[i] >= 63 && arg[i] <= 64) || (arg[i] >= 91 && arg[i] <= 94)
			|| arg[i] == 96 || (arg[i] >= 123 && arg[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}

void	export_filter(t_export *export, t_cmd *data)
{
	if (is_export(export->var))
	{
		if (export->var)
			add_to_env(export, &data->data->env);
		data->data->last_exit_code = 0;
	}
	else
	{
		write(2,
		ft_strjoin3("minishell: export: `", export->var, "': not a valid identifier\n"),
			ft_strlen(export->var) + 47);
		data->data->last_exit_code = 1;
	}
}

int	export_exist(t_export *export, char ***env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(export->var);
	while ((*env)[i])
	{
		if (ft_strncmp(export->var, (*env)[i], len) == 0)
		{
			if (*export->value)
				(*env)[i] = ft_strjoin3(export->var, "=", export->value);
			else if (export->is_equal)
				(*env)[i] = ft_strjoin(export->var, "=");
			else if (!*export->value)
				return (1);
			else
				(*env)[i] = ft_strdup(export->var);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
  I should always use `ft_bzero()` to make sure no garbage value has been taken!
 */
void	parse_export(t_export **export, char *arg)
{
	int	export_len;
	int	var_len;

	if (!*export)
		*export = ft_collector(sizeof(t_export), ALLOC);
	ft_bzero(*export, sizeof(t_export));
	export_len = ft_strlen(arg);
	var_len = export_len - ft_strlen(ft_strchr(arg, '='));
	if (ft_strchr(arg, '='))
		(*export)->is_equal = 1;
	(*export)->var = ft_strndup(arg, var_len);
	if (!((export_len - (var_len + 1)) <= 0))
		(*export)->value = ft_strndup(arg + (var_len + 1) , (export_len - (var_len + 1)));
	else
		(*export)->value = "\0";
}

void	export_analyser(t_export *export, t_cmd *data)
{
	if (export_exist(export, &data->data->env))
		return ;
	else
		export_filter(export, data);
}

void	export_printer(char **env)
{
	t_export	*export;
	char		*var;
	char		*value;
	int			i;
	char		*full_expo;

	i = 0;
	while (env[i])
	{
		export = NULL;
		parse_export(&export, env[i]);
		var = export->var;
		value = ft_strjoin3("\"", export->value, "\"");
		if (export->is_equal)
			full_expo = ft_strjoin3("declare -> ", ft_strjoin3(var, "=", value), "\n");
		else
			full_expo = ft_strjoin3("declare -> ", var, "\n");
		write(1,  full_expo, ft_strlen(full_expo));
		i++;
	}
}

int	do_export(t_cmd *data)
{
	t_export	*export;
	int			i;

	i = 0;
	export = NULL;
	++data->argv;
	if (!*data->argv)
		export_printer(data->data->env);
	else
	{
		while (data->argv[i])
		{
			parse_export(&export, data->argv[i]);
			export_analyser(export, data);
			i++;
		}
	}
	data->data->last_exit_code = 0;
	return (1);
}
