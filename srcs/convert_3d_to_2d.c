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

float	*calculate_projection_x_and_y(t_app *fdf, int x, int y)
{
	float	*coordinates;
	int		z;

	coordinates = (float *)malloc(sizeof(float) * 2);
	if (!coordinates)
		exit_error(fdf, MALLOC_ERR);
	z = fdf->world_space[y][x].z * 1;
	// coordinates[X] = ((float)x - (float)y) / sqrtf(2);
	// coordinates[Y] = ((float)x + (float)y - 2 * (float)z) / sqrtf(6);
	coordinates[X] = (x - y) * cosf(deg_to_rad(fdf->projection_angle));
	coordinates[Y] = (x + y) * sinf(deg_to_rad(fdf->projection_angle)) - z;
	coordinates[X] += 50;
	coordinates[Y] += 50;
	return (coordinates);
}

float	deg_to_rad(float deg)
{
	return (deg * (M_PI/180));
}
