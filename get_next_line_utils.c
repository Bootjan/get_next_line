/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:00:01 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/16 13:12:53 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(const char *str, char c)
{
	size_t	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*clean_data(char *data)
{
	char	*out;
	int		i;
	int		index_n;

	if (!data)
		return (NULL);
	index_n = ft_strchr(data, '\n');
	i = ft_strlen(data) - index_n - 1;
	if (i == 0 || index_n == -1)
		return (NULL);
	out = malloc((i + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (data[index_n + i + 1])
	{
		out[i] = data[index_n + i + 1];
		i++;
	}
	out[i] = '\0';
	free(data);
	return (out);
}

char	*free_list(t_buffers **list, int i)
{
	t_buffers	*current;
	t_buffers	*next;

	if (!*list)
		return (NULL);
	current = *list;
	while (current && (i == -1 || i > 1))
	{
		next = current->next;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
		i--;
	}
	if (current && i == 1)
	{
		current->data = clean_data(current->data);
		if (!current->data)
		{
			free(current);
			current = NULL;
		}
	}
	*list = current;
	return (NULL);
}

int	lpush_back(t_buffers **list, char *data)
{
	t_buffers	*elem;
	t_buffers	*current;

	elem = malloc(sizeof(t_buffers));
	if (!elem)
	{
		free_list(list, -1);
		return (0);
	}
	elem->data = data;
	elem->next = NULL;
	current = *list;
	if (!current)
	{
		*list = elem;
		return (1);
	}
	while (current->next)
		current = current->next;
	current->next = elem;
	return (1);
}
