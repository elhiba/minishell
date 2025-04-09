/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/09 20:34:39 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

execut

int	main(int ac, char **av, char **env)
{
	t_input	input;

	(void) ac;
	(void) av;
	ft_bzero(&input, sizeof(input));
	input.env = env;
	handle_signals();
	while (1)
	{
		input.readline_in = readline("$> ");
		if (input.readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(input.readline_in);
		ft_parse(&input);
		ft_builtin(&input);
		execute_cmd(input);
		free(input.readline_in);
	}
	return (0);
}
