/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:53:20 by alegeber          #+#    #+#             */
/*   Updated: 2025/07/06 17:14:57 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_and_return_null(char *line, char *buffer)
{
	if (line)
		free(line);
	if (buffer)
		buffer[0] = '\0';
	return (NULL);
}

static char	*append_chunk_to_line(char *line, char *buffer, int chunk_len)
{
	char	*new_line;
	size_t	old_line_len;

	old_line_len = ft_strlen(line);
	new_line = (char *)malloc(sizeof(char) * (old_line_len + chunk_len + 1));
	if (!new_line)
		return (free_and_return_null(line, NULL));
	ft_memcpy(new_line, line, old_line_len);
	ft_memcpy(new_line + old_line_len, buffer, chunk_len);
	new_line[old_line_len + chunk_len] = '\0';
	free(line);
	return (new_line);
}

static int	read_into_buffer(int fd, char *buffer)
{
	int	read_bytes;

	read_bytes = read(fd, buffer, BUFFER_SIZE);
	if (read_bytes >= 0)
		buffer[read_bytes] = '\0';
	return (read_bytes);
}

static char	*process_buffer(char *line, char *buffer, int *read_bytes)
{
	int	newline_pos;

	newline_pos = ft_strpos(buffer, '\n');
	if (newline_pos != -1)
	{
		line = append_chunk_to_line(line, buffer, newline_pos + 1);
		if (!line)
			return (NULL);
		ft_memmove(buffer, buffer + newline_pos + 1, ft_strlen(buffer
				+ newline_pos + 1));
		buffer[ft_strlen(buffer + newline_pos + 1)] = '\0';
		*read_bytes = 0;
		return (line);
	}
	line = append_chunk_to_line(line, buffer, ft_strlen(buffer));
	if (!line)
		return (NULL);
	buffer[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	read_bytes = 1;
	while (read_bytes > 0)
	{
		if (*buffer)
		{
			line = process_buffer(line, buffer, &read_bytes);
			if (!line || read_bytes == 0)
				return (line);
		}
		read_bytes = read_into_buffer(fd, buffer);
	}
	if (read_bytes < 0 || !*line)
		return (free_and_return_null(line, buffer));
	return (line);
}

// #include <stdio.h>   // Für printf
// #include <fcntl.h>   // Für open
// #include "get_next_line.h"

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2 // no filename as arg
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error: File couldn't be opened.\n");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
