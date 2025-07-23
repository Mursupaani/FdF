/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/23 14:07:28 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	draw_pixels_on_window(t_app *fdf)
{
	int	x;
	int	y;

	calculate_bounding_box(fdf);
	calculate_centering_offset(fdf);
	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			draw_pixel(fdf, x, y);
			x++;
		}
		y++;
	}
	draw_lines_between_points(fdf);
}

void	calculate_centering_offset(t_app *fdf)
{
	float	map_width_proj;
	float	map_height_proj;

	map_width_proj = fdf->proj_max_x + fdf->proj_min_x;
	map_height_proj = fdf->proj_max_y + fdf->proj_min_y;
	fdf->x_centering_offset = WIN_WIDTH / 2.0f - map_width_proj / 2;
	fdf->y_centering_offset = WIN_HEIGHT / 2.0f - map_height_proj / 2;
}

void	draw_pixel(t_app *fdf, int x, int y)
{
	fdf->screen[y][x].x = round(fdf->screen[y][x].x + fdf->x_centering_offset);
	fdf->screen[y][x].y = round(fdf->screen[y][x].y + fdf->y_centering_offset);
	pixel_to_image(fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, 0x00FFFFFF);
}

void	reset_image(t_app *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(
		fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
}

void	update_image(t_app *fdf)
{
		reset_image(fdf);
		draw_pixels_on_window(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
}
