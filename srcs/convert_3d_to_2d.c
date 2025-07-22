/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_3d_to_2d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:32:23 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 14:08:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static float	deg_to_rad(float deg);
static float	calculate_x_projection(t_app *fdf, int x, int y);
static float	calculate_y_projection(t_app *fdf, int x, int y, int z);

void	calculate_projection_x_and_y(t_app *fdf, int x, int y)
{
	float	z;
	
	z = fdf->world[y][x].z * fdf->z_scalar;
	fdf->screen[y][x].z = (int)round(z);
	fdf->screen[y][x].x = (int)round(calculate_x_projection(fdf, x, y));
	fdf->screen[y][x].y = (int)round(calculate_y_projection(fdf, x, y, z));
	fdf->screen[y][x].x += fdf->x_centering_offset;
	fdf->screen[y][x].y += fdf->y_centering_offset;
}

static float	calculate_x_projection(t_app *fdf, int x, int y)
{
	float	x_proj;

	x_proj = (x - y) * cosf(deg_to_rad(fdf->projection_angle));
	return (x_proj);
}

static float	calculate_y_projection(t_app *fdf, int x, int y, int z)
{
	float	y_proj;

	y_proj = (x + y) * sinf(deg_to_rad(fdf->projection_angle)) - z;
	return (y_proj);
}

static float	deg_to_rad(float deg)
{
	return (deg * (M_PI/180));
}
