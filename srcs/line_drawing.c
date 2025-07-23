/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:24:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/23 14:09:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	draw_line_between_two_points(t_app *fdf, int line_end_points[]);

void	draw_lines_between_points(t_app *fdf)
{
	int	x;
	int	y;
	int	line_end_points[4];

	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			line_end_points[X0] = fdf->screen[y][x].x;
			line_end_points[Y0] = fdf->screen[y][x].y;
			if (x + 1 < fdf->matrix_width)
			{
				line_end_points[X1] = fdf->screen[y][x + 1].x;
				line_end_points[Y1] = fdf->screen[y][x + 1].y;
				draw_line_between_two_points(fdf, line_end_points);
			}
			if (y + 1 < fdf->matrix_height)
			{
				line_end_points[X1] = fdf->screen[y + 1][x].x;
				line_end_points[Y1] = fdf->screen[y + 1][x].y;
				draw_line_between_two_points(fdf, line_end_points);
			}
			x++;
		}
		y++;
	}
}

static void	draw_line_between_two_points(t_app *fdf, int line_end_points[])
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	x0 = line_end_points[X0];
	y0 = line_end_points[Y0];
	x1 = line_end_points[X1];
	y1 = line_end_points[Y1];
	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;

	while (true)
	{
		pixel_to_image(fdf, x0, y0, fdf->default_color);
		if (x0 == x1
			&& y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
