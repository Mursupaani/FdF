/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/15 19:21:16 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	count_matrix_height(t_app *fdf);
static int	count_matrix_width(t_app *fdf);

//WARN: Make void?
int	**parse_fdf_file(t_app *fdf)
{
	fdf->matrix = (int **)malloc(sizeof(int *));
	if (!fdf->matrix)
		exit_error(fdf, MALLOC_ERR);
	count_matrix_height(fdf);

	return (fdf->matrix);
}

//WARN: Make void?
static int	count_matrix_height(t_app *fdf)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	line_count = 0;
	line = get_next_line(fd);
	if (line)
		line_count++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			line_count++;
	}
	close(fd);
	fdf->matrix_height = line_count;
	return (line_count);
}

static int	count_matrix_width(t_app *fdf)
{

}
