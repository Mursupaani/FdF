/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 11:34:21 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	parse_lines(t_app *fdf);
static void	parse_split_line(t_app *fdf, char *split_line[], int x, int y);

//WARN: Make void?
t_pixel	**parse_fdf_file(t_app *fdf)
{
	count_matrix_dimensions(fdf);
	if (fdf->matrix_height == 0 || fdf->matrix_width == 0)
		exit_error(fdf, PARSING_ERR);
	fdf->world = initialize_pixel_matrix(fdf);
	if (!fdf->world)
		exit_error(fdf, MALLOC_ERR);
	fdf->screen = initialize_pixel_matrix(fdf);
	if (!fdf->screen)
		exit_error(fdf, MALLOC_ERR);
	parse_lines(fdf);
	return (fdf->world);
}

static void	parse_lines(t_app *fdf)
{
	int		fd;
	char	*line;
	char	**split_line;
	int		y;
	int		x;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		line = get_next_line(fd);
		if (!line)
			exit_error(fdf, GET_NEXT_LINE_ERR);
		split_line = ft_split(line, ' ');
		free(line);
		if (!split_line)
			exit_error(fdf, MALLOC_ERR);
		parse_split_line(fdf, split_line, x, y);
		free(split_line);
		y++;
	}
	close(fd);
}

static void	parse_split_line(t_app *fdf, char *split_line[], int x, int y)
{
	while (x < fdf->matrix_width)
	{
		save_pixel_coordinates(fdf->world, x, y, ft_atoi(split_line[x]));
		free(split_line[x]);
		x++;
	}
	free(split_line[x]);
}
