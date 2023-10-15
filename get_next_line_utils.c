/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:00:01 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 18:07:28 by bschaafs         ###   ########.fr       */
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

char	*free_function(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

char	*ft_strdup(char **buffer, int r)
{
	char	*out;
	int		i;

	out = malloc((r + 1) * sizeof(char));
	if (!out)
		return (free_function(buffer));
	i = 0;
	while ((*buffer)[i])
	{
		out[i] = (*buffer)[i];
		i++;
	}
	out[i] = '\0';
	free_function(buffer);
	return (out);
}

char	*ft_strjoin(char **temp, char **buffer, int r)
{
	char	*out;
	int		i;
	int		j;

	out = malloc((ft_strlen(*temp) + r + 1) * sizeof(char));
	if (!out)
	{
		free_function(buffer);
		return (free_function(temp));
	}
	i = 0;
	j = 0;
	while ((*temp)[i])
		out[j++] = (*temp)[i++];
	i = 0;
	while ((*buffer)[i])
		out[j++] = (*buffer)[i++];
	out[j] = '\0';
	free_function(temp);
	free_function(buffer);
	return (out);
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
