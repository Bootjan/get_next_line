/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/13 16:44:13 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*compute_new_temp(char **temp, int len, int new_line_index)
{
	char	*out;
	size_t	j;

	out = malloc((len - new_line_index + 1) * sizeof(char));
	if (!out)
	{
		free_function(temp);
		return (NULL);
	}
	j = 0;
	while ((*temp)[new_line_index])
		out[j++] = (*temp)[new_line_index++];
	out[j] = '\0';
	return (out);
}

void	clean_temp(char **temp, char **str, int new_line_index)
{
	char	*out;
	int		len;

	if (!*temp)
	{
		free_function(str);
		return ;
	}
	len = ft_strlen(*temp);
	if (new_line_index == len)
	{
		free_function(temp);
		return ;
	}
	out = compute_new_temp(temp, len, new_line_index);
	if (!out)
		return ;
	free(*temp);
	*temp = out;
}

char	*next_line(char **temp)
{
	int		i;
	int		j;
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
		return (free_function(temp));
	j = 0;
	while (j < i)
	{
		out[j] = (*temp)[j];
		j++;
	}
	out[j] = '\0';
	clean_temp(temp, &out, i);
	return (out);
}

char	*compute_buffer(char **temp, int fd, int *r)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_function(temp));
	*r = read(fd, buffer, BUFFER_SIZE);
	if (*r == -1)
	{
		free_function(&buffer);
		return (free_function(temp));
	}
	if (*r == 0 && !*temp)
		return (free_function(&buffer));
	return (buffer);
}

char	*get_next_line(int fd)
{
	int			r;
	char		*buffer;
	static char	*temp;

	r = 1;
	while (r)
	{
		buffer = compute_buffer(&temp, fd, &r);
		if (r == 0)
			break ;
		if (!buffer)
			return (NULL);
		buffer[r] = '\0';
		if (!temp)
			temp = ft_strdup(&buffer, r);
		else
			temp = ft_strjoin(&temp, &buffer, r);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	return (next_line(&temp));
}
