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
static int	count_matrix_width(t_app *fdf, char *line);
// static void	parse_lines(t_app *fdf);

//WARN: Make void?
int	**parse_fdf_file(t_app *fdf)
{
	count_matrix_height(fdf);
	fdf->matrix = (int **)malloc(sizeof(int *) * fdf->matrix_height);
	if (!fdf->matrix)
		exit_error(fdf, MALLOC_ERR);
	
	return (fdf->matrix);
}

//WARN: Make void?
static int	count_matrix_height(t_app *fdf)
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
	if (fdf->matrix_width != line_width)
		exit_error(fdf, PARSING_ERR);
	return (line_width);
}

// static void	parse_lines(t_app *fdf)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;
// 	int		j;
//
// 	fd = open(fdf->file_path, O_RDONLY);
// 	if (fd == -1)
// 		exit_error(fdf, FD_ERR);
// 	i = 0;
// 	j = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		fdf->matrix[i][j] = 0;
// 	}
//
// }
