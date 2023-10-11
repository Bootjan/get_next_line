/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:04:59 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/11 16:41:46 by bschaafs         ###   ########.fr       */
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

char	*clean_next_line(char *line)
{
	size_t	i;
	char	*out;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	out = malloc((i + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		out[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		out[i++] = '\n';
	out[i] = '\0';
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
			return (NULL); //free
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			return (NULL); //free
		if (r == 0)
			break ;
		buffer[r] = '\0';
		if (!temp)
			temp = ft_strdup(buffer);
		else
			temp = ft_strjoin(temp, buffer);
		buffer = NULL;
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	if (r == 0 && ft_strlen(temp) == 0)
		return (NULL);
	return (clean_next_line(temp));
}



int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *out = get_next_line(fd);
	printf(";%s;\n", out);
	out = get_next_line(fd);
	printf(";%s;\n", out);
	out = get_next_line(fd);
	printf(";%s;\n", out);
	out = get_next_line(fd);
	printf(";%s;\n", out);
	out = get_next_line(fd);
	printf(";%s;\n", out);
	if (out)
		free(out);
	close(fd);
}