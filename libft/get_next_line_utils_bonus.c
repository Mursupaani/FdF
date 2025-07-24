/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/06/13 10:43:54 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

bool	add_node_back(t_buf **head, char *buf)
{
	t_buf	*temp;
	t_buf	*node;

	node = (t_buf *)malloc(sizeof(t_buf));
	if (!node)
		return (false);
	node->buf = buf;
	node->next = NULL;
	temp = *head;
	if (!(*head))
		*head = node;
	else
	{
		while (temp)
		{
			if ((temp)->next == NULL)
			{
				(temp)->next = node;
				return (true);
			}
			temp = temp->next;
		}
	}
	return (true);
}

void	free_list(t_buf **head, t_buf *new_head)
{
	t_buf	*temp;

	while (*head)
	{
		temp = (*head)->next;
		free((*head)->buf);
		free(*head);
		*head = temp;
	}
	if (new_head && new_head->buf && !new_head->buf[0])
	{
		free(new_head->buf);
		free(new_head);
	}
	else
		*head = new_head;
}

bool	find_new_line(t_buf *buf_head)
{
	int	i;

	if (!buf_head)
		return (false);
	while (buf_head->next)
		buf_head = buf_head->next;
	while (buf_head)
	{
		i = 0;
		while (buf_head->buf[i])
		{
			if (buf_head->buf[i] == '\n')
				return (true);
			i++;
		}
		buf_head = buf_head->next;
	}
	return (false);
}

bool	store_leftover_to_head(t_buf **head)
{
	t_buf	*new_head;
	char	*buf_remainder;

	if (!head)
		return (false);
	buf_remainder = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf_remainder)
		return (false);
	buf_remainder[0] = '\0';
	copy_remainder_to_new_head(*head, buf_remainder);
	new_head = (t_buf *)malloc(sizeof(t_buf));
	if (!new_head)
		return (false);
	new_head->buf = buf_remainder;
	new_head->next = NULL;
	free_list(head, new_head);
	return (true);
}

void	copy_remainder_to_new_head(t_buf *head, char *buf_remainder)
{
	t_buf	*last_node;
	size_t	i;
	size_t	j;

	if (!head || !buf_remainder)
		return ;
	last_node = head;
	while (last_node->next)
		last_node = last_node->next;
	i = 0;
	j = 0;
	while (last_node->buf[i])
	{
		if (last_node->buf[i++] == '\n')
		{
			while (last_node->buf[i])
				buf_remainder[j++] = last_node->buf[i++];
			buf_remainder[j] = '\0';
			break ;
		}
	}
}
