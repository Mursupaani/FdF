/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 13:09:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	dda_matrix_corner(t_app *fdf, int x, int y, int z);
static void	dda_matrix_edge(t_app *fdf, int x, int y, int z);
static void	dda_matrix_inside(t_app *fdf, int x, int y, int z);

void	dda(t_app *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y + 1 < fdf->matrix_height)
	{
		x = 0;
		while (x + 1 < fdf->matrix_width)
		{
			if ((y == 0 || y + 1 == fdf->matrix_height)
			&& (x == 0 || x + 1 == fdf-> matrix_width))
				dda_matrix_corner(fdf, x, y, fdf->matrix[x][y]);
			else if ((y != 0 && y + 1 != fdf->matrix_height)
				&& (x != 0 && x + 1 != fdf->matrix_width))
				dda_matrix_inside(fdf, x, y, fdf->matrix[x][y]);
			else
				dda_matrix_edge(fdf, x, y, fdf->matrix[x][y]);
			x++;
		}
		y++;
	}
}

static void	dda_matrix_corner(t_app *fdf, int x, int y, int z)
{
	float	dx;
	float	dy;
	float	dz;

	dx = abs(x + 1 - x);
	dy = abs(y + 1 - y);
	dz = abs(fdf->matrix[x + 1][y + 1] - z);
	(void)dz;
}

static void	dda_matrix_edge(t_app *fdf, int x, int y, int z)
{

}

static void	dda_matrix_inside(t_app *fdf, int x, int y, int z)
{

}
