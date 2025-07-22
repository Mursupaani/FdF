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

static void	dda_matrix_corner(t_app *fdf, int x, int y)
{
	float	dx;
	float	dy;

	calculate_projection_x_and_y(fdf, x, y);
	pixel_to_image(fdf, fdf->screen[y][x].x, fdf->screen[y][x].y, 0x00FFFFFF);
	(void)dx;
	(void)dy;
}
