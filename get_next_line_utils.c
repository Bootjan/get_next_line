/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:00:01 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/13 15:41:11 by bschaafs         ###   ########.fr       */
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

char	*free_function(char **str1, char **str2, int n)
{
	if (n > 0 && *str1)
		free(*str1);
	*str1 = NULL;
	if (n > 1 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	return (NULL);
}

char	*ft_strdup(char **buffer)
{
	char	*out;
	int		i;

	out = malloc((ft_strlen(*buffer) + 1) * sizeof(char));
	if (!out)
		return (free_function(buffer, NULL, 1));
	i = 0;
	while ((*buffer)[i])
	{
		out[i] = (*buffer)[i];
		i++;
	}
	out[i] = '\0';
	free_function(buffer, NULL, 1);
	return (out);
}

char	*ft_strjoin(char **temp, char **buffer)
{
	char	*out;
	int		i;
	int		j;

	out = malloc((ft_strlen(*temp) + ft_strlen(*buffer) + 1) * sizeof(char));
	if (!out)
		return (free_function(temp, buffer, 2));
	i = 0;
	j = 0;
	while ((*temp)[i])
		out[j++] = (*temp)[i++];
	i = 0;
	while ((*buffer)[i])
		out[j++] = (*buffer)[i++];
	out[j] = '\0';
	free_function(temp, buffer, 2);
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
