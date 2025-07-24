/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 11:08:17 by anpollan         ###   ########.fr       */
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

void	draw_pixel(t_app *fdf, int x, int y)
{
	int	color;

	if (fdf->screen[y][x].color == -1)
		color = fdf->default_color;
	else
		color = fdf->screen[y][x].color;
	fdf->screen[y][x].x = round(fdf->screen[y][x].x + fdf->x_centering_offset);
	fdf->screen[y][x].y = round(fdf->screen[y][x].y + fdf->y_centering_offset);
	pixel_to_image(
		fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, color);
}

void	change_z_depth(t_app *fdf, int keycode)
{
	if (keycode == XK_w)
		fdf->z_scalar += 0.1f;
	if (keycode == XK_q)
		fdf->z_scalar -= 0.1f;
	update_image(fdf);
}

void	update_image(t_app *fdf)
{
	reset_image(fdf);
	draw_pixels_on_window(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
}
