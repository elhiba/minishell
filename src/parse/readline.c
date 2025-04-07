/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/07 12:02:50 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Waiting for a good idea to parse!*/
void	ft_parse(t_data *vars)
{
	(void)vars;
}

void	ft_readline(t_data *vars)
{
	while (1)
	{
		vars->readline_in = readline("$> ");
		if (vars->readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		ft_parse(vars);
		printf("%s\n", vars->readline_in);
		add_history(vars->readline_in);
		free(vars->readline_in);
	}
}
