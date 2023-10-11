/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:04:59 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/11 19:30:31 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	clean_temp(char **temp)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!*temp)
	{
		*temp = NULL;
		return ;
	}
	if (!ft_strchr(*temp, '\n'))
		return ;
	i = 0;
	while ((*temp)[i] && (*temp)[i] != '\n')
		i++;
	out = malloc((ft_strlen(*temp) - i++) * sizeof(char));
	if (!out)
		return ;
	j = 0;
	while ((*temp)[i])
		out[j++] = (*temp)[i++];
	out[j] = '\0';
	if (*temp)
		free(*temp);
	*temp = out;
}

char	*clean_next_line(char **temp, int r)
{
	size_t	i;
	char	*out;

	if (!*temp)
		return (NULL);
	i = 0;
	while ((*temp)[i] && (*temp)[i] != '\n')
		i++;
	if ((*temp)[i] == '\n')
		i++;
	out = malloc((i + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while ((*temp)[i] && (*temp)[i] != '\n')
	{
		out[i] = (*temp)[i];
		i++;
	}
	if ((*temp)[i] == '\n')
		out[i++] = '\n';
	out[i] = '\0';
	if (r == 0)
		*temp = NULL;
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*buffer;
	int			r;

	clean_temp(&temp);
	r = 1;
	while (r)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (free_function(temp, buffer));
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			return (free_function(temp, buffer));
		if (r == 0)
			break ;
		buffer[r] = '\0';
		// printf("buffer: %s\n", buffer);
		if (!temp)
			temp = ft_strdup(buffer);
		else
			temp = ft_strjoin(temp, buffer);
		if (!temp)
			return (free_function(temp, buffer));
		buffer = NULL;
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	return (clean_next_line(&temp, r));
}

void	leakschecker(void)
{
	system("leaks -q a.out");  
}


int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *out = get_next_line(fd);
	printf("Newline: %s\n", out);
	out = get_next_line(fd);
	printf("Newline: %s\n", out);
	out = get_next_line(fd);
	printf("Newline: %s\n", out);
	out = get_next_line(fd);
	printf("Newline: %s\n", out);
	out = get_next_line(fd);
	printf("Newline: %s\n", out);
	out = get_next_line(fd);
	printf("Newline: %s\n", out);
	if (out)
		free(out);
	close(fd);
	atexit(leakschecker);
}

