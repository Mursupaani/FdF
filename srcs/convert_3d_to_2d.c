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

float	*calculate_destination_x_and_y(t_app *fdf, int x, int y)
{
	float	*coordinates;
	float	alpha;
	int		z;

	alpha = fdf->projection_angle;
	coordinates = (float *)malloc(sizeof(float) * 2);
	if (!coordinates)
		exit_error(fdf, MALLOC_ERR);
	z = fdf->matrix[y][x];
	// coordinates[X] = ((float)x - (float)z) / 2 + 50;
	// coordinates[Y] = ((float)x + (float)y * 2 + (float)z) / 6 + 50;
	// (void)alpha;
	coordinates[X] = x * cosf(deg_to_rad(alpha)) + y * cosf(deg_to_rad(alpha + 120)) + z * cosf(deg_to_rad(alpha - 120)) + 50;
	coordinates[Y] = x * sinf(deg_to_rad(alpha)) + y * sinf(deg_to_rad(alpha + 120)) + z * sinf(deg_to_rad(alpha - 120)) + 50;
	return (coordinates);
}
