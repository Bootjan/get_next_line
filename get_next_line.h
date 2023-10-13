/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:01:30 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/13 15:44:27 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> // remove when turning in

size_t	ft_strlen(const char *s);
char	*ft_strdup(char **buffer);
char	*ft_strjoin(char **dst, char **src);
int		ft_strchr(const char *dst, char c);
char	*get_next_line(int fd);
char	*free_function(char **str);

#endif