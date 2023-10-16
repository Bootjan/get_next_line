/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 23:39:34 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*compute_buffer(t_buffers **list, int fd, int *r)
{
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_list(list, -1));
	*r = read(fd, buffer, BUFFER_SIZE);
	if (*r == -1)
		return (free_list(list, -1)); // free buffer
	if (*r == 0)
		return (free_list(list, -1));
	buffer[*r] = '\0';
	return (buffer);
}

char	*make_string(t_buffers **list, int elements, int length)
{
	char		*out;
	int			i;
	int			j;
	t_buffers	*current;

	out = malloc((length + 1) * sizeof(char));
	if (!out)
		return (free_list(list, -1));
	current = *list;
	i = 0;
	while (current && elements--)
	{
		j = 0;
		while (current->data[j] && i < elements)
			out[i++] = current->data[j++];
		current = current->next;
	}
	out[i] = '\0';
	free_list(list, i + 1);
	return (out);
}

char	*next_line(t_buffers **list, int *index)
{
	char		*out;
	int			len;
	t_buffers	*current;
	int			contains_n;

	if (!*list)
		return (NULL);
	*index = 0;
	current = *list;
	while (current)
	{
		contains_n = ft_strchr(current->data, '\n');
		if (contains_n >= 0)
			return (make_string(list, *index + 1, len + contains_n + 1));
		len += ft_strlen(current->data);
		current = current->next;
		*index++;
	}
	return (make_string(list, *index, len));
}

char	*get_next_line(int fd)
{
	static t_buffers	*list;
	char				*buffer;
	int					r;
	int					index_n;

	r = 1;
	index_n = ft_strchr(buffer, '\n');
	while (r)
	{
		buffer = compute_buffer(&list, fd, &r);
		if (!buffer)
			return (NULL);
		if (r == 0)
			break ;
		if (!buffer)
			return (NULL);
		if (!lpush_back(&list, buffer))
			return (NULL);
		index_n = ft_strchr(buffer, '\n');
		if (index_n >= 0)
			break ;
	}
	return (next_line(&list, &index_n));
}
