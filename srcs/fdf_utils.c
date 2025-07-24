/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:15:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 10:16:10 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

t_pixel	**initialize_pixel_matrix(t_app *fdf)
{
	t_pixel	**space;
	int		i;

	space = (t_pixel **)malloc(sizeof(t_pixel *) * fdf->matrix_height);
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	if (!space)
		exit_error(fdf, MALLOC_ERR);
	i = 0;
	while (i < fdf->matrix_height)
	{
		space[i] = (t_pixel *)ft_calloc(1, sizeof(t_pixel) * fdf->matrix_width);
		if (!space[i])
			exit_error(fdf, MALLOC_ERR);
		i++;
	}
	return (space);
}
