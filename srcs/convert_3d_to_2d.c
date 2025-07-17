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
	int		z;

	coordinates = (float *)malloc(sizeof(float) * 2);
	if (!coordinates)
		exit_error(fdf, MALLOC_ERR);
	z = fdf->matrix[y][x];
	coordinates[X] = (x - y) * cos(fdf->projection_angle);
	coordinates[Y] = (x + y) * sin(fdf->projection_angle) - z;
	return (coordinates);
}
