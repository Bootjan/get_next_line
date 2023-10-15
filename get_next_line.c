/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 21:31:25 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*compute_new_temp(char **temp, int len, int new_line_index)
{
	char	*out;
	size_t	j;

	out = malloc((len - new_line_index) * sizeof(char));
	if (!out)
	{
		free_function(temp);
		return (NULL);
	}
	j = 0;
	new_line_index++;
	while ((*temp)[new_line_index])
		out[j++] = (*temp)[new_line_index++];
	out[j] = '\0';
	return (out);
}

void	clean_temp(char **temp, char **str, int new_line_index, int len)
{
	char	*out;

	if (!*temp)
	{
		free_function(str);
		return ;
	}
	if (new_line_index + 1 == len || new_line_index == -1)
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

char	*next_line(char **temp, int new_line_index, int len)
{
	int		j;
	char	*out;
	int		malloc_size;

	if (!*temp)
		return (NULL);
	malloc_size = new_line_index + 1;
	if (new_line_index == -1)
		malloc_size = len;
	out = malloc((malloc_size + 1) * sizeof(char));
	if (!out)
		return (free_function(temp));
	j = 0;
	while (j < malloc_size)
	{
		out[j] = (*temp)[j];
		j++;
	}
	out[j] = '\0';
	clean_temp(temp, &out, new_line_index, len);
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
	if (*r == 0)
		return (free_function(&buffer));
	buffer[*r] = '\0';
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
	new_line_index = ft_strchr(temp, '\n');
	while (r)
	{
		buffer = compute_buffer(&temp, fd, &r);
		if (r == 0)
			break ;
		if (!buffer)
			return (NULL);
		if (!temp)
			temp = ft_strdup(&buffer, r, &temp_len);
		else
			temp = ft_strjoin(&temp, &buffer, r, &temp_len);
		new_line_index = ft_strchr(temp, '\n');
		if (new_line_index >= 0)
			break ;
	}
	return (next_line(&temp, new_line_index, temp_len));
}













int	lpush_back(t_list **list, char *data)
{
	t_list	*elem;
	t_list	*current;

	elem = malloc(sizeof(t_list));
	if (!elem)
	{
		free_list(list);
		return (0);
	}
	elem->data = data;
	current = *list;
	if (!current)
	{
		current = elem;
		return (1);
	}
	while (current->next)
		current = current->next;
	current->next = elem;
	return (1);
}

char	*free_list(t_list **list, int i)
{
	t_list	*current;
	t_list	*next;

	if (!list)
		return ;
	current = *list;
	while (current && (i == -1 || i > 0))
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
	*list = current;
	return (NULL);
}

char	*next_line(t_list **list)
{
	char	*out;
	int		i;
	int		len;
	t_list	*current;
	int		contains_n;

	if (!*list)
		return (NULL);
	i = 0;
	current = *list;
	while (current)
	{
		contains_n = ft_strchr(current->data, '\n');
		if (contains_n >= 0)
		{
			out = make_string(list, i + 1, len + contains_n + 1);
			if (!out)
				return (free_list(list, -1));
			free_list(list, i + 1);
			return (out);
		}
		len += ft_strlen(current->data);
		current = current->next;
		i++;
	}
	out = make_string(list, i, len);
	if (!out)
		return (free_list(list, -1));
	return (out);
}
