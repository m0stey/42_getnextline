/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:53:20 by alegeber          #+#    #+#             */
/*   Updated: 2025/07/04 18:03:22 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_stash(char *stash)
{
	char	*new_stash;
	char	*nl_ptr;
	size_t	i;

	nl_ptr = gnl_strchr(stash, '\n');
	if (!nl_ptr || *(nl_ptr + 1) == '\0')
		return (NULL);
	new_stash = (char *)malloc(gnl_strlen(nl_ptr + 1) + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	nl_ptr++;
	while (*nl_ptr)
		new_stash[i++] = *nl_ptr++;
	new_stash[i] = '\0';
	return (new_stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	char	*nl_ptr;
	size_t	len;
	size_t	i;

	nl_ptr = gnl_strchr(stash, '\n');
	if (nl_ptr)
		len = (nl_ptr - stash) + 1;
	else
		len = gnl_strlen(stash);
	if (len == 0)
		return (NULL);
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_and_update_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp_stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_update_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	temp_stash = stash;
	stash = clean_stash(temp_stash);
	free(temp_stash);
	return (line);
}
