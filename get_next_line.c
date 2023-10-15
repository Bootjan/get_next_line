/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 18:30:18 by bschaafs         ###   ########.fr       */
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

char	*next_line(char **temp, int new_line_index)
{
	int		i;
	int		j;
	char	*out;

	if (!*temp)
		return (NULL);
	if (new_line_index == -1)
		new_line_index = ft_strlen(*temp);
	out = malloc((new_line_index + 1) * sizeof(char));
	if (!out)
		return (free_function(temp));
	j = 0;
	while (j < new_line_index)
	{
		out[j] = (*temp)[j];
		j++;
	}
	out[j] = '\0';
	clean_temp(temp, &out, new_line_index);
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
	buffer[r] = '\0';
	return (buffer);
}

char	*get_next_line(int fd)
{
	int			r;
	char		*buffer;
	static char	*temp;
	int			new_line_index;
	int			temp_len;

	r = 1;
	temp_len = ft_strlen(temp);
	while (r)
	{
		buffer = compute_buffer(&temp, fd, &r);
		if (r == 0)
			break ;
		if (!buffer)
			return (NULL);
		new_line_index = ft_strchr(buffer, '\n');
		if (!temp)
			temp = ft_strdup(&buffer, r, &temp_len);
		else
			temp = ft_strjoin(&temp, &buffer, r, &temp_len);
		if (new_line_index >= 0)
			break ;
	}
	if (buffer)
		free(buffer);
	return (next_line(&temp, new_line_index));
}
