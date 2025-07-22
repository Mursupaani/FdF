/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:37:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/15 19:30:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	free_matrix(t_app *fdf, t_pixel **space);

void	exit_success(t_app *fdf)
{
	if (fdf)
		free_memory(fdf);
	exit(EXIT_SUCCESS);
}

void	exit_error(t_app *fdf, int error)
{
	if (fdf)
		free_memory(fdf);
	if (error == FILETYPE_ERR)
		ft_putstr_fd("is_fdf_file: Invalid file type.\n", STDERR_FILENO);
	if (error == FD_ERR)
		perror("open");
	if (error == FDF_STRUCT_ERR)
		perror("malloc");
	else if (error == MLX_INIT_ERR)
		perror("mlx_init");
	else if (error == MLX_WIN_ERR)
		perror("mlx_win");
	else if (error == MLX_IMG_ERR)
		perror("mlx_new_image");
	if (error == MATRIX_ERR)
		ft_putstr_fd("parse_fdf_file: Error in creating matrix.\n", STDERR_FILENO);
	if (error == PARSING_ERR)
		ft_putstr_fd("parse_fdf_file: Error in file contents.\n", STDERR_FILENO);
	if (error == GET_NEXT_LINE_ERR)
		ft_putstr_fd("get_next_line: Something went wrong.\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_memory(t_app *fdf)
{
	if (!fdf)
		return ;
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->mlx_win)
		mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	if (fdf->world)
		free_matrix(fdf, fdf->world);
	if (fdf->screen)
		free_matrix(fdf, fdf->screen);
	free(fdf);
}

static void	free_matrix(t_app *fdf, t_pixel **space)
{
	int	i;

	i = 0;
	if (!fdf || !space)
		return ;
	while (i < fdf->matrix_height)
		free(space[i++]);
	free(space);
}
