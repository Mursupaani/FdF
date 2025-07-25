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
static bool	parse_split_line(t_app *fdf, char *split_line[], int x, int y);
static bool	parse_pos_and_color(t_app *fdf, char *temp[], int x, int y);
static void	free_string_array(char **arr[], int i);

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
		if (!split_line || !parse_split_line(fdf, split_line, x, y))
			exit_error(fdf, PARSING_ERR);
		free(split_line);
		y++;
	}
	close(fd);
}

static bool	parse_split_line(t_app *fdf, char *split_line[], int x, int y)
{
	char	**temp;

	while (x < fdf->matrix_width)
	{
		temp = ft_split(split_line[x], ',');
		if (!temp || !temp[0])
		{
			free_string_array(&split_line, x);
			exit_error(fdf, PARSING_ERR);
		}
		if (!parse_pos_and_color(fdf, temp, x, y))
		{
			free_string_array(&split_line, x);
			return (false);
		}
		free(split_line[x]);
		x++;
	}
	free(split_line[x]);
	return (true);
}

static bool	parse_pos_and_color(t_app *fdf, char *temp[], int x, int y)
{
	int		*temp_val;
	int		val;

	temp_val = ft_atoi_safe(temp[0]);
	if (!temp_val)
	{
		free_string_array(&temp, 0);
		return (false);
	}
	val = *temp_val;
	save_pixel_coordinates(fdf->world, x, y, val);
	if (temp[1])
	{
		temp_val = ft_atoi_hexadecimal_safe(temp[1]);
		if (!temp_val)
		{
			free_string_array(&temp, 0);
			return (false);
		}
		fdf->world[y][x].color = (unsigned int)*temp_val;
	}
	else
		fdf->world[y][x].color = -1;
	free_string_array(&temp, 0);
	return (true);
}

static void	free_string_array(char **arr[], int i)
{
	if (!*arr)
		return ;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
