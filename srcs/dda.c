/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 12:45:48 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"


static void	dda_matrix_corner();
static void	dda_matrix_edge();
static void	dda_matrix_inside();

void	dda(t_app *fdf)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	y = 0;
	while (y + 1 < fdf->matrix_height)
	{
		x = 0;
		while (x + 1 < fdf->matrix_width)
		{
			if ((y == 0 || y + 1 == fdf->matrix_height)
			&& (x == 0 || x + 1 == fdf-> matrix_width))
				dda_matrix_corner();
			else if ((y != 0 && y + 1 != fdf->matrix_height)
				&& (x != 0 && x + 1 != fdf->matrix_width))
				dda_matrix_inside();
			else
				dda_matrix_edge();
		}
	}
}

static void	dda_matrix_corner()
{

}
