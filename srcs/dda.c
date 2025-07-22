/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 14:35:26 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	dda_matrix_corner(t_app *fdf, int x, int y);

void	draw_pixels_on_window(t_app *fdf)
{
	int	x;
	int	y;

	calculate_centering_offset(fdf);
	if (!fdf->screen)
		fdf->screen = initialize_pixel_matrix(fdf);
	if (!fdf->screen)
		exit_error(fdf, MALLOC_ERR);
	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			dda_matrix_corner(fdf, x, y);
			x++;
		}
		y++;
	}
}

void	calculate_centering_offset(t_app *fdf)
{
	float	map_width_proj;
	float	map_height_proj;

	map_width_proj = fdf->proj_max_x + fdf->proj_min_x;
	map_height_proj = fdf->proj_max_y + fdf->proj_min_y;
	fdf->x_centering_offset = SCREEN_WIDTH / 2.0f - map_width_proj / 2;
	fdf->y_centering_offset = SCREEN_HEIGHT / 2.0f - map_height_proj / 2;
	ft_printf("x offset: %d\n", (int)fdf->x_centering_offset);
	ft_printf("y offset: %d\n", (int)fdf->y_centering_offset);
}


static void	dda_matrix_corner(t_app *fdf, int x, int y)
{
	fdf->screen[y][x].y += fdf->x_centering_offset;
	fdf->screen[y][x].x += fdf->y_centering_offset;
	pixel_to_image(fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, 0x00FFFFFF);
}
