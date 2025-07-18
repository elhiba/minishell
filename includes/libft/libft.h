/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:29:39 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/18 16:26:25 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../gcft/gc_collector.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/* Garbage Collector */
void				*ft_collector(size_t size, int flag);

/* libft */
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
char				*ft_itoa(int n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
#endif
