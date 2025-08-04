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
		line->start_r = (unsigned char)(line->start_color >> 16);
		line->start_g = (unsigned char)(line->start_color >> 8);
		line->start_b = (unsigned char)(line->start_color);
		// ft_printf("start r test: %d\n", line->start_color >> 16);
		// ft_printf("start r: %d\n", line->start_r);
		// ft_printf("start g: %d\n", line->start_g);
		// ft_printf("start b: %d\n", line->start_b);
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
		// ft_printf("end r: %d\n", line->end_r);
		// ft_printf("end g: %d\n", line->end_g);
		// ft_printf("end b: %d\n", line->end_b);
	}
}
