/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:53:16 by alegeber          #+#    #+#             */
/*   Updated: 2025/07/04 17:59:10 by alegeber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	char	find;

	find = (char)c;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == find)
			return ((char *)s);
		s++;
	}
	if (find == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *stash, char *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!stash)
	{
		stash = (char *)malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	new_str = (char *)malloc(gnl_strlen(stash) + gnl_strlen(buffer) + 1);
	if (!new_str)
		return (free(stash), NULL);
	i = -1;
	j = 0;
	while (stash[++i])
		new_str[i] = stash[i];
	while (buffer[j])
		new_str[i++] = buffer[j++];
	new_str[i] = '\0';
	free(stash);
	return (new_str);
}
