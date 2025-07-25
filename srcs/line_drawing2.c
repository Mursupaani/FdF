/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:13:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/25 14:03:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	store_line_start(t_app *fdf, t_line_calc *line, int x, int y)
{
	line->x0 = fdf->screen[y][x].x;
	line->y0 = fdf->screen[y][x].y;
	if (fdf->screen[y][x].color == -1)
		line->start_color = fdf->default_color;
	else
	{
		line->start_color = fdf->screen[y][x].color;
		line->start_r = (unsigned char)(line->start_color >> 16) & 0xFF;
		line->start_g = (unsigned char)(line->start_color >> 8) & 0xFF;
		line->start_b = (unsigned char)(line->start_color) & 0xFF;
	}
}

void	store_line_end(t_app *fdf, t_line_calc *line, int x, int y)
{
	line->x1 = fdf->screen[y][x].x;
	line->y1 = fdf->screen[y][x].y;
	if (fdf->screen[y][x].color == -1)
		line->end_color = fdf->default_color;
	else
	{
		line->end_color = fdf->screen[y][x].color;
		line->end_r = (unsigned char)(line->end_color >> 16) & 0xFF;
		line->end_g = (unsigned char)(line->end_color >> 8) & 0xFF;
		line->end_b = (unsigned char)(line->end_color) & 0xFF;
	}
}
