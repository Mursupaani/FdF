/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:24:27 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/25 13:14:15 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	draw_line_between_two_points(t_app *fdf, t_line_calc line);
static void	init_line_calc_struct(t_line_calc *line);
static void	calculate_color_change(t_line_calc *line);

void	draw_lines_between_points(t_app *fdf)
{
	t_line_calc	line;
	int			x;
	int			y;

	y = 0;
	while (y < fdf->matrix_height)
	{
		x = 0;
		while (x < fdf->matrix_width)
		{
			store_line_start(fdf, &line, x, y);
			if (x + 1 < fdf->matrix_width)
			{
				store_line_end(fdf, &line, x + 1, y);
				draw_line_between_two_points(fdf, line);
			}
			if (y + 1 < fdf->matrix_height)
			{
				store_line_end(fdf, &line, x, y + 1);
				draw_line_between_two_points(fdf, line);
			}
			x++;
		}
		y++;
	}
}

static void	draw_line_between_two_points(t_app *fdf, t_line_calc line)
{
	unsigned int	color;

	init_line_calc_struct(&line);
	calculate_color_change(&line);
	color = line.start_color;
	while (true)
	{
		color += ((int)line.r_change << 16) & 0xFFFFFFFF
			+ ((int)line.g_change << 8) & 0xFFFFFFFF
			+ line.g_change & 0xFFFFFFFF;
		pixel_to_image(fdf, line.x0, line.y0, color);
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

static void	init_line_calc_struct(t_line_calc *line)
{
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

static void	calculate_color_change(t_line_calc *line)
{
	int	line_len;
	int	r_diff;
	int	g_diff;
	int	b_diff;

	line_len = round(sqrt(pow(line->dx, 2) + pow(line->dy, 2)));
	if (line_len != 0)
	{
		r_diff = line->end_r - line->start_r;
		g_diff = line->end_g - line->start_g;
		b_diff = line->end_b - line->start_b;
		line->r_change = r_diff / line_len;
		line->g_change = g_diff / line_len;
		line->b_change = b_diff / line_len;
	}
	else
	{
		line->r_change = 0;
		line->g_change = 0;
		line->b_change = 0;
	}
}
