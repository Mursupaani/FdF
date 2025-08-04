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
static void	calculate_current_color(t_line_calc *line);

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
	init_line_calc_struct(&line);
	calculate_color_change(&line);
	line.cur_color = line.start_color;
	while (true)
	{
		calculate_current_color(&line);
		pixel_to_image(fdf, line.x0, line.y0, line.cur_color);
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
	line->cur_r_f = line->start_r;
	line->cur_g_f = line->start_g;
	line->cur_b_f = line->start_b;
}

static void	calculate_color_change(t_line_calc *line)
{
	int		line_len;

	line_len = round(sqrt(pow(line->dx, 2) + pow(line->dy, 2)));
	if (line_len != 0)
	{
		line->r_change = (float)(line->end_r - line->start_r) / line_len;
		line->g_change = (float)(line->end_g - line->start_g) / line_len;
		line->b_change = (float)(line->end_b - line->start_b) / line_len;
	}
	else
	{
		line->r_change = 0.0f;
		line->g_change = 0.0f;
		line->b_change = 0.0f;
	}
}

static void	calculate_current_color(t_line_calc *line)
{
	int	cur_r;
	int	cur_g;
	int	cur_b;

	line->cur_r_f += line->r_change;
	line->cur_g_f += line->g_change;
	line->cur_b_f += line->b_change;
	cur_r = fminf(fmaxf(roundf(line->cur_r_f), 0), 255);
	cur_g = fminf(fmaxf(roundf(line->cur_g_f), 0), 255);
	cur_b = fminf(fmaxf(roundf(line->cur_b_f), 0), 255);
	line->cur_color = (cur_r << 16) + (cur_g << 8) + cur_b;
}
