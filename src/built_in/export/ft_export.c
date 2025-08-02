/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 16:14:37 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
 * ------------------- THO HOLY EXPORT ------------------------
 *							DONE								
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
		if (export->var)
			write(2, ft_strjoin3("minishell: export: `",
					export->var, "': not a valid identifier\n"),
				ft_strlen(export->var) + 47);
		else
			write(2,
				ft_strjoin3("minishell: export: `", "=",
					"': not a valid identifier\n"), ft_strlen(export->var) + 47);
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
			else if (export->var && export->is_equal)
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

	*export = ft_collector(sizeof(t_export), ALLOC);
	ft_bzero(*export, sizeof(t_export));
	export_len = ft_strlen(arg);
	var_len = export_len - ft_strlen(ft_strchr(arg, '='));
	if (ft_strchr(arg, '='))
		(*export)->is_equal = 1;
	(*export)->var = ft_strndup(arg, var_len);
	if (!((export_len - (var_len + 1)) <= 0))
		(*export)->value = ft_strndup(arg + (var_len + 1),
				(export_len - (var_len + 1)));
	else
		(*export)->value = ft_strdup("");
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
