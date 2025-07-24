/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:26:55 by anpollan          #+#    #+#             */
/*   Updated: 2025/06/13 10:43:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_buf
{
	char			*buf;
	struct s_buf	*next;
}	t_buf;

char	*get_next_line(int fd);
void	free_list(t_buf **head, t_buf *new_head);
bool	store_leftover_to_head(t_buf **head);
bool	add_node_back(t_buf **head, char *buf);
void	copy_remainder_to_new_head(t_buf *head, char *buf_remainder);
bool	find_new_line(t_buf *buffer);
char	*get_line(t_buf *head);
size_t	get_next_line_len(t_buf *head);
bool	create_buf_list(t_buf **buf_head, int fd);
void	copy_line(t_buf *head, char *next_line);

#endif
