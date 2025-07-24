/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:32:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 11:33:57 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	count_matrix_dimensions(t_app *fdf)
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

void	count_matrix_width(t_app *fdf, char *line)
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
	if (line_width > fdf->matrix_width)
		fdf->matrix_width = line_width;
}

void	save_pixel_coordinates(t_pixel **space, int x, int y, int z)
{
	if (!space)
		return ;
	space[y][x].x = x;
	space[y][x].y = y;
	space[y][x].z = z;
}
