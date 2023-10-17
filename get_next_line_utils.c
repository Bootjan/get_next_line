/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:46:11 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/17 17:51:22 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_function(char **temp)
{
	if (*temp)
		free(*temp);
	*temp = NULL;
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
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

char	*ft_strdup(char *buffer)
{
	char	*out;
	size_t	length;
	size_t	i;

	length = ft_strlen(buffer);
	if (length == 0)
		return (NULL);
	out = malloc((length + 1) * SIZE_OF_CHAR);
	if (!out)
		return (NULL);
	i = 0;
	while (i < length)
	{
		out[i] = buffer[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*ft_strjoin(char **temp, char *buffer)
{
	char	*out;
	size_t	length;
	size_t	i;
	size_t	j;

	length = ft_strlen(*temp) + ft_strlen(buffer);
	if (length == 0)
		return (free_function(temp));
	out = malloc((length + 1) * SIZE_OF_CHAR);
	if (!out)
		return (free_function(temp));
	i = 0;
	j = 0;
	while ((*temp)[j])
		out[i++] = (*temp)[j++];
	j = 0;
	while (buffer[j])
		out[i++] = buffer[j++];
	out[i] = '\0';
	free_function(temp);
	return (out);
}
