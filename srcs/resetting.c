/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resetting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:10:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 10:18:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	reset_image(t_app *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(
			fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
}

void	reset_view(t_app *fdf)
{
	reset_view_settings(fdf);
	update_image(fdf);
}
