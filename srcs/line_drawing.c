/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:24:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 12:53:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	draw_line_between_two_points(t_app *fdf, int line_ends[]);
static void	init_line_calc_struct(t_line_calc *line, int line_ends[]);
static void	store_line_ends(t_app *fdf, int end, int x, int y);

void	draw_lines_between_points(t_app *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			store_line_ends(fdf, 0, x, y);
			if (x + 1 < fdf->matrix_width)
			{
				store_line_ends(fdf, 1, x + 1, y);
				draw_line_between_two_points(fdf, fdf->line_ends);
			}
			if (y + 1 < fdf->matrix_height)
			{
				store_line_ends(fdf, 1, x, y + 1);
				draw_line_between_two_points(fdf, fdf->line_ends);
			}
			x++;
		}
		y++;
	}
}

static void	store_line_ends(t_app *fdf, int end, int x, int y)
{
	if (end == 0)
	{
		fdf->line_ends[X0] = fdf->screen[y][x].x;
		fdf->line_ends[Y0] = fdf->screen[y][x].y;
	}
	if (end == 1)
	{
		fdf->line_ends[X1] = fdf->screen[y][x].x;
		fdf->line_ends[Y1] = fdf->screen[y][x].y;
	}
}

static void	draw_line_between_two_points(t_app *fdf, int line_ends[])
{
	t_line_calc	line;

	init_line_calc_struct(&line, line_ends);
	while (true)
	{
		pixel_to_image(fdf, line.x0, line.y0, fdf->default_color);
		if (line.x0 == line.x1
			&& line.y0 == line.y1)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			line.x0 += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

static void	init_line_calc_struct(t_line_calc *line, int line_ends[])
{
	line->x0 = line_ends[X0];
	line->y0 = line_ends[Y0];
	line->x1 = line_ends[X1];
	line->y1 = line_ends[Y1];
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
}
