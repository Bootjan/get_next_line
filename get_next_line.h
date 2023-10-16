/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:30 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 23:38:21 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*free_list(t_list **list, int i);
int		lpush_back(t_list **list, char *data);
int		ft_strchr(const char *dst, char c);
char	*get_next_line(int fd);
char	*free_function(char **str);

typedef struct s_buffers {
	char	*data;
	struct	s_buffer *next;
}	t_buffers;

#endif