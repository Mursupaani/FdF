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

	map_width_proj = fdf->proj_max_x - fdf->proj_min_x;
	map_height_proj = fdf->proj_max_y - fdf->proj_min_y;

	fdf->x_centering_offset = (WIN_WIDTH / 2.0f) - (fdf->proj_min_x + map_width_proj / 2.0f) + fdf->x_move_view;
	fdf->y_centering_offset = (WIN_HEIGHT / 2.0f) - (fdf->proj_min_y + map_height_proj / 2.0f) + fdf->y_move_view;
}

void	draw_pixel(t_app *fdf, int x, int y)
{
	fdf->screen[y][x].x = round(fdf->screen[y][x].x + fdf->x_centering_offset);
	fdf->screen[y][x].y = round(fdf->screen[y][x].y + fdf->y_centering_offset);
	pixel_to_image(fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, fdf->default_color);
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
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
}

void	reset_view(t_app *fdf)
{
	reset_view_settings(fdf);
	update_image(fdf);
}

void	change_color(t_app *fdf, char operation)
{
	static int	i;
	int			colors[8];

	colors[0] = 0xFFFFFF;
	colors[1] = 0x065535;
	colors[2] = 0xffc0cb;
	colors[3] = 0x008080;
	colors[4] = 0xe6e6fa;
	colors[5] = 0xffa500;
	colors[6] = 0xd3ffce;
	colors[7] = 0x003366;
	if (operation == '+')
		i++;
	if (operation == '-')
		i--;
	if (i < 0)
		i = 7;
	if (i > 7)
		i = 0;
	fdf->default_color = colors[i];
}
