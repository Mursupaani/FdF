/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:25:54 by anpollan          #+#    #+#             */
/*   Updated: 2025/06/13 10:41:48 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_buf	*list_heads[MAX_FD];
	char			*next_line;

	if (fd == -2)
	{
		fd = 0;
		while (fd < MAX_FD)
			free_list(&list_heads[fd++], NULL);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	next_line = NULL;
	if (!create_buf_list(&list_heads[fd], fd))
	{
		free_list(&list_heads[fd], NULL);
		return (NULL);
	}
	next_line = get_line(list_heads[fd]);
	if (!next_line || !store_leftover_to_head(&list_heads[fd]))
		free_list(&list_heads[fd], NULL);
	return (next_line);
}

bool	create_buf_list(t_buf **buf_head, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;

	while (!find_new_line(*buf_head))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (false);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read || bytes_read < 0)
		{
			free(buffer);
			if (bytes_read < 0)
				return (false);
			return (true);
		}
		buffer[bytes_read] = '\0';
		if (!add_node_back(buf_head, buffer))
		{
			free(buffer);
			return (false);
		}
	}
	return (true);
}

size_t	get_next_line_len(t_buf *head)
{
	t_buf	*temp;
	size_t	next_line_len;
	size_t	i;

	if (!head)
		return (0);
	next_line_len = 0;
	temp = head;
	while (temp)
	{
		i = 0;
		while (temp->buf[i] && temp->buf[i] != '\n')
		{
			next_line_len++;
			i++;
		}
		if (temp->buf[i] == '\n')
		{
			next_line_len++;
			return (next_line_len);
		}
		temp = temp->next;
	}
	return (next_line_len);
}

char	*get_line(t_buf *head)
{
	char	*next_line;

	if (!head)
		return (NULL);
	next_line = (char *)malloc(sizeof(char) * (get_next_line_len(head) + 1));
	if (!next_line)
		return (NULL);
	copy_line(head, next_line);
	return (next_line);
}

void	copy_line(t_buf *head, char *next_line)
{
	t_buf	*temp;
	size_t	i;
	size_t	j;

	if (!next_line || !head)
		return ;
	temp = head;
	i = 0;
	while (temp)
	{
		j = 0;
		while (temp->buf[j] && temp->buf[j] != '\n')
			next_line[i++] = temp->buf[j++];
		if (temp->buf[j] == '\n')
		{
			next_line[i++] = '\n';
			next_line[i] = '\0';
			return ;
		}
		temp = temp->next;
	}
	next_line[i] = '\0';
}
