/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/16 13:00:32 by bschaafs         ###   ########.fr       */
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
	{
		free(buffer);
		return (free_list(list, -1)); // free buffer
	}
	if (*r == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*r] = '\0';
	return (buffer);
}

char	*make_string(t_buffers **list, int elements, int length)
{
	char		*out;
	int			i;
	int			j;
	t_buffers	*current;
	int			elems_done;

	out = malloc((length + 1) * sizeof(char));
	if (!out)
		return (free_list(list, -1));
	current = *list;
	i = 0;
	elems_done = 0;
	while (current && elems_done++ < elements)
	{
		j = 0;
		while (current->data[j] && i < length--)
			out[i++] = (char)current->data[j++];
		current = current->next;
	}
	out[i] = '\0';
	free_list(list, elements);
	return (out);
}

char	*next_line(t_buffers **list)
{
	int			len;
	t_buffers	*current;
	int			contains_n;
	int			index;

	if (!*list)
		return (NULL);
	index = 0;
	len = 0;
	current = *list;
	while (current)
	{
		contains_n = ft_strchr(current->data, '\n');
		if (contains_n >= 0)
			return (make_string(list, index + 1, len + contains_n + 1));
		len += ft_strlen(current->data);
		current = current->next;
		index++;
	}
	return (make_string(list, index, len));
}

char	*get_next_line(int fd)
{
	static t_buffers	*list;
	char				*buffer;
	int					r;
	int					index_n;

	r = 1;
	while (r)
	{
		buffer = compute_buffer(&list, fd, &r);
		if (!buffer && !list)
			return (NULL);
		if (r == 0)
			break ;
		if (!lpush_back(&list, buffer))
			return (NULL);
		index_n = ft_strchr(buffer, '\n');
		if (index_n >= 0)
			break ;
	}
	return (next_line(&list));
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main()
// {
// 	int fd = open("text.txt", O_RDONLY);
// 	char *out = get_next_line(fd);
// 	printf(";%s;\n", out);
// 	out = get_next_line(fd);
// 	printf(";%s;\n", out);
// 	out = get_next_line(fd);
// 	printf(";%s;\n", out);
// 	out = get_next_line(fd);
// 	printf(";%s;\n", out);
// 	if (out)
// 		free(out);
// 	close(fd);
// }
