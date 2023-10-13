/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/13 15:41:20 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*compute_return_value(char **temp, int len, int i)
{
	char	*out;
	size_t	j;

	out = malloc((len - i + 1) * sizeof(char));
	if (!out)
	{
		free_function(temp, NULL, 1);
		return (NULL);
	}
	j = 0;
	while ((*temp)[i])
		out[j++] = (*temp)[i++];
	out[j] = '\0';
	return (out);
}

void	clean_temp(char **temp, char **str)
{
	char	*out;
	int		len;
	int		i;

	if (!*temp)
	{
		free_function(str, NULL, 1);
		return ;
	}
	len = ft_strlen(*temp);
	i = len - ft_strchr(*temp, '\n');
	if (i == len)
	{
		free_function(temp, NULL, 1);
		return ;
	}
	out = compute_return_value(temp, len, i);
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
		return (free_function(temp, NULL, 1));
	j = 0;
	while (j < i)
	{
		out[j] = (*temp)[j];
		j++;
	}
	out[j] = '\0';
	clean_temp(temp, &out);
	return (out);
}

char	*compute_buffer(char **temp, int fd)
{
	char	*buffer;
	int		r;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_function(temp, NULL, 1));
	r = read(fd, buffer, BUFFER_SIZE);
	if (r == -1)
		return (free_function(temp, &buffer, 2));
	if (r == 0 && !*temp)
		return (free_function(&buffer, NULL, 1));
	if (r == 0)
		return (NULL);
	buffer[r] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*temp;

	while (1)
	{
		buffer = compute_buffer(&temp, fd);
		if (!buffer)
			return (NULL);
		if (!temp)
			temp = ft_strdup(&buffer);
		else
			temp = ft_strjoin(&temp, &buffer);
		if (ft_strchr(temp, '\n') >= 0)
			break ;
	}
	if (buffer)
		free(buffer);
	return (next_line(&temp));
}
