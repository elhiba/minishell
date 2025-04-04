/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/04 20:57:05 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_readline(void)
{
	char	*readline_in;

	while (1)
	{
		readline_in = readline("$> ");
		if (readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		printf("%s\n", readline_in);
		free(readline_in);
	}
}
