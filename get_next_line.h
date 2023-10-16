/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:30 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/16 14:02:18 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_buffers {
	char				*data;
	struct s_buffers	*next;
}	t_buffers;

size_t	ft_strlen(const char *s);
void	free_list(t_buffers **list, int i);
int		lpush_back(t_buffers **list, char *data);
int		ft_strchr(const char *dst, char c);
char	*get_next_line(int fd);
char	*free_function(char **str);
char	*get_next_line(int fd);

#endif