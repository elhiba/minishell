/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/04/09 15:19:17 by sel-maaq         ###   ########.fr       */
=======
/*   Updated: 2025/04/09 15:57:55 by moel-hib         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * this is not a complete functions!
 */
int	do_cd(char *path)
{		
	if (chdir(path) == -1)
		error_handler(path);
	return (0);
}
