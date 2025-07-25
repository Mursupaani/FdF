/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:13:01 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/25 12:28:42 by anpollan         ###   ########.fr       */
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
		line->start_color = fdf->screen[y][x].color;
}

void	store_line_end(t_app *fdf, t_line_calc *line, int x, int y)
{
	line->x1 = fdf->screen[y][x].x;
	line->y1 = fdf->screen[y][x].y;
	if (fdf->screen[y][x].color == -1)
		line->end_color = fdf->default_color;
	else
		line->end_color = fdf->screen[y][x].color;
}
