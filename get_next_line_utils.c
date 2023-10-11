/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:01:54 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/11 18:59:21 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(const char *dst, char c)
{
	size_t	i;

	if (!dst)
		return (0);
	i = 0;
	while (dst[i])
	{
		if (dst[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *dst, char *src)
{
	size_t	i;
	size_t	j;
	char	*out;

	out = malloc((ft_strlen(dst) + ft_strlen(src) + 1) * sizeof(char));
	if (!out)
		return (free_function(dst, src));
	i = 0;
	j = 0;
	while (dst[i])
		out[j++] = dst[i++];
	i = 0;
	while (src[i])
		out[j++] = src[i++];
	out[j] = '\0';
	free_function(dst, src);
	return (out);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*out;

	if (!s)
		return (NULL);
	out = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!out)
	{
		if (s)
			free(s);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	if (s)
		free(s);
	return (out);
}

char	*free_function(char *temp, char *buf)
{
	if (temp)
		free(temp);
	if (buf)
		free(buf);
	return (NULL);
}
