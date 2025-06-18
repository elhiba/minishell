/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:39:51 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 16:30:40 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_COLLECTOR_H
# define GC_COLLECTOR_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>

typedef struct s_collector
{
	void				*addr;

	struct s_collector	*next;
}	t_collector;

typedef enum s_flag
{
	ALLOC,
	FREE,
	EXIT
}	t_flag;

void	*ft_collector(size_t size, int flag);
#endif
