/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:30:51 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/31 09:56:28 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
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

void	export_analyser(t_export *export, t_cmd *data)
{
	if (is_export(export->var))
	{
		if (export_exist(export, &data->data->env))
			return ;
		else
			export_filter(export, data);
	}
	else
		export_filter(export, data);
}

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort(char ***env)
{
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
	{
		j = i + 1;
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[i], (*env)[j]) > 0)
				swap(&(*env)[i], &(*env)[j]);
			j++;
		}
		i++;
	}
}

void	export_printer(char **env)
{
	t_export	*export;
	char		*var;
	char		*value;
	int			i;
	char		*full_expo;

	i = 0;
	sort(&env);
	while (env[i])
	{
		export = NULL;
		parse_export(&export, env[i]);
		var = export->var;
		value = ft_strjoin3("\"", export->value, "\"");
		if (export->is_equal)
			full_expo = ft_strjoin3("declare -> ",
					ft_strjoin3(var, "=", value), "\n");
		else
			full_expo = ft_strjoin3("declare -> ", var, "\n");
		write(1,  full_expo, ft_strlen(full_expo));
		i++;
	}
}
