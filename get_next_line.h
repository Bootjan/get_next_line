/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:48:21 by bschaafs          #+#    #+#             */
/*   Updated: 2023/12/16 23:10:05 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# define SIZE_OF_CHAR 1

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
int		ft_contains_n(const char *str, char c);
char	*ft_tempdup(char *buffer);
char	*ft_tempjoin(char **temp, char *buffer);
char	*free_function(char **str);
char	*get_next_line(int fd);

#endif