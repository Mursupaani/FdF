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
	float	x_proj;
	float	y_proj;
	
	z = fdf->world[y][x].z * fdf->z_scalar;
	fdf->screen[y][x].z = (z);
	x_proj = (calculate_x_projection(fdf, x, y));
	y_proj = (calculate_y_projection(fdf, x, y, z));
	x_proj *= fdf->img_scalar;
	y_proj *= fdf->img_scalar;
	fdf->screen[y][x].x = x_proj;
	fdf->screen[y][x].y = y_proj;
}

void	calculate_bounding_box(t_app *fdf)
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
			calculate_projection_x_and_y(fdf, x, y);
			if (fdf->screen[y][x].x < fdf->proj_min_x)
				fdf->proj_min_x = fdf->screen[y][x].x;
			if (fdf->screen[y][x].x > fdf->proj_max_x)
				fdf->proj_max_x = fdf->screen[y][x].x;
			if (fdf->screen[y][x].y < fdf->proj_min_y)
				fdf->proj_min_y = fdf->screen[y][x].y;
			if (fdf->screen[y][x].y > fdf->proj_max_y)
				fdf->proj_max_y = fdf->screen[y][x].y;
			x++;
		}
		y++;
	}
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
