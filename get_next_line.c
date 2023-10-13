/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:47:39 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/13 13:10:32 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_temp(char *temp)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	if (i == ft_strlen(temp))
		return (free_function(temp, NULL, 1));
	out = malloc((ft_strlen(temp) - i + 1) * sizeof(char));
	if (!out)
		return (free_function(temp, NULL, 1));
	j = 0;
	while (temp[i + j])
	{
		out[j] = temp[i + j];
		j++;
	}
	out[j] = '\0';
	free_function(temp, NULL, 1);
	if (!temp)
		return (free_function(out, NULL, 1));
	return (out);
}

char	*next_line(char *temp)
{
	int		i;
	int		j;
	char	*out;

	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	out = malloc((i + 1) * sizeof(char));
	if (!out)
		return (free_function(temp, NULL, 1));
	j = 0;
	while (j++ < i)
	{
		out[j] = temp[j];
		j++;
	}
	out[j] = '\0';
	temp = clean_temp(temp);
	return (out);
}

char	*get_next_line(int fd)
{
	int			r;
	char		*buffer;
	static char	*temp;

	r = 1;
	while (r)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (free_function(temp, NULL, 1));
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
			return (free_function(temp, buffer, 2));
		if (r == 0)
			break ;
		buffer[r] = '\0';
		if (!temp)
			temp = ft_strdup(buffer);
		else
			temp = ft_strjoin(temp, buffer);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if (buffer)
		free(buffer);
	return (next_line(temp));
}
