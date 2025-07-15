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

void	exit_error(t_mlx *mlx)
{
	if (mlx)
		free_memory(mlx);
	exit(EXIT_FAILURE);
}

void	free_memory(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->img)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		ft_printf("destroy image\n");
	}
	if (mlx->mlx_win)
	{
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		ft_printf("destroy window\n");
	}
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		ft_printf("destroy display\n");
	}
	if (mlx)
	{
	free(mlx);
		ft_printf("freed mlx\n");
	}
}
