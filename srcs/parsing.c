/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:44:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 13:07:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static int	count_matrix_dimensions(t_app *fdf);
static int	count_matrix_width(t_app *fdf, char *line);
static void	parse_lines(t_app *fdf);

//WARN: Make void?
t_pixel	**parse_fdf_file(t_app *fdf)
{
	count_matrix_dimensions(fdf);
	if (fdf->matrix_height == 0 || fdf->matrix_width == 0)
		exit_error(fdf, PARSING_ERR);
	fdf->world = initialize_pixel_matrix(fdf);
	parse_lines(fdf);
	return (fdf->world);
}

t_pixel **initialize_pixel_matrix(t_app *fdf)
{
	t_pixel	**space;
	int		i;

	space = (t_pixel **)malloc(sizeof(t_pixel *) * fdf->matrix_height);
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	i = 0;
	while (i < fdf->matrix_height)
	{
		space[i] = (t_pixel *)ft_calloc(1, sizeof(t_pixel) * fdf->matrix_width);
		if (!space[i])
			exit_error(fdf, MALLOC_ERR);
		i++;
	}
	return (space);
}

//WARN: Make void?
static int	count_matrix_dimensions(t_app *fdf)
{
	int		fd;
	char	*line;

	fd = open(fdf->file_path, O_RDONLY);
	if (fd == -1)
		exit_error(fdf, FD_ERR);
	line = get_next_line(fd);
	if (line)
	{
		fdf->matrix_height++;
		count_matrix_width(fdf, line);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
		{
			count_matrix_width(fdf, line);
			fdf->matrix_height++;
		}
	}
	close(fd);
	return (fdf->matrix_height);
}

//WARN: Make void?
static int	count_matrix_width(t_app *fdf, char *line)
{
	int		line_width;
	int		i;

	line_width = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && line[i] != '\0')
			line_width++;
		while (ft_isdigit(line[i]) && line[i] != '\0')
			i++;
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		if (!ft_strncmp(&line[i], "\n", 2) && (line[i + 1]) == '\0')
			i++;
		if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\0')
		{	
			free(line);
			exit_error(fdf, PARSING_ERR);
		}
	}
	if (fdf->matrix_width == 0)
		fdf->matrix_width = line_width;
	// if (fdf->matrix_width != line_width)
	// {
	// 	free(line);
	// 	exit_error(fdf, PARSING_ERR);
	// }
	return (line_width);
}

static void	parse_lines(t_app *fdf)
{
	int		fd;
	char	*line;
	char	**temp;
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
		temp = ft_split(line, ' ');
		free(line);
		if (!temp)
			exit_error(fdf, MALLOC_ERR);
		while (x < fdf->matrix_width)
		{
			save_pixel_coordinates_to_matrix(fdf->world, x, y, ft_atoi(temp[x]));
			free(temp[x]);
			x++;
		}
		free(temp[x]);
		free(temp);
		y++;
	}
	close(fd);
}

void	save_pixel_coordinates_to_matrix(t_pixel **space, int x, int y, int z)
{
	if (!space)
		return ;
	space[y][x].x = x;
	space[y][x].y = y;
	space[y][x].z = z;
}
