/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_and_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:37:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/14 20:57:03 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	exit_success(t_mlx *mlx)
{
	if (mlx)
		free_memory(mlx);
	exit(EXIT_SUCCESS);
}

void	exit_error(t_mlx *mlx, int error)
{
	if (mlx)
		free_memory(mlx);
	if (error == FILETYPE_ERR)
		ft_putstr_fd("is_fdf_file: Invalid file type.\n", STDERR_FILENO);
	if (error == FD_ERR)
		perror("open");
	if (error == MLX_STRUCT_ERR)
		perror("malloc");
	else if (error == MLX_INIT_ERR)
		perror("mlx_init");
	else if (error == MLX_WIN_ERR)
		perror("mlx_win");
	else if (error == MLX_IMG_ERR)
		perror("mlx_new_image");
	exit(EXIT_FAILURE);
}

void	free_memory(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->mlx_win)
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
}
