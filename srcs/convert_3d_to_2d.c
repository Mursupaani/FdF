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
	int		alpha;

	alpha = 30;
	coordinates = (float *)malloc(sizeof(float) * 2);
	if (!coordinates)
		exit_error(fdf, MALLOC_ERR);
	z = fdf->matrix[y][x] * 1;
	// coordinates[X] = ((float)x - (float)y) / sqrtf(2);
	// coordinates[Y] = ((float)x + (float)y - 2 * (float)z) / sqrtf(6);
	coordinates[X] = (x - y) * cosf(deg_to_rad(alpha));
	coordinates[Y] = (x + y) * sinf(deg_to_rad(alpha)) - z;
	coordinates[X] += 50;
	coordinates[Y] += 50;
	return (coordinates);
}
