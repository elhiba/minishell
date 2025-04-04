/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/02 22:15:12 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
	static char	*readline_in;

	signal_init();

	while (1)
	{
		readline_in = readline("$>");
		if (readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		printf("%s\n", readline_in);
		free(readline_in);
		
	}

	return (0);
}
