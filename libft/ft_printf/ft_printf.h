/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:54:36 by sel-maaq          #+#    #+#             */
/*   Updated: 2024/11/23 11:49:59 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

typedef struct s_flags
{
	int	plus;
	int	space;
	int	hash;
}	t_flags;

int		ft_printf(const char *s, ...);
t_flags	handle_flags(const char *str, int *i);
int		handle_format(const char *str, va_list args, int *i);

int		ft_putnbr(int n);
int		ft_putnbr_flags(int n, t_flags flags);
int		ft_print_unsigned(unsigned int n);
int		ft_print_hex(unsigned int n, char format, t_flags flags);
int		ft_print_hex_recursive(unsigned int n, char format);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_hex_ptr(unsigned long long n);

int		check_format(const char *str);
int		is_format(char c);
int		is_flag(char c);

#endif