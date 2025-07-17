/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 12:54:29 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"


static void	dda_matrix_corner(t_app *fdf, int x_val, int y_val);
static void	dda_matrix_edge(t_app *fdf, int x_val, int y_val);
static void	dda_matrix_inside(t_app *fdf, int x_val, int y_val);

void	dda(t_app *fdf)
{
	int	x_val;
	int	y_val;

	y_val = 0;
	while (y_val + 1 < fdf->matrix_height)
	{
		x_val = 0;
		while (x_val + 1 < fdf->matrix_width)
		{
			if ((y_val == 0 || y_val + 1 == fdf->matrix_height)
			&& (x_val == 0 || x_val + 1 == fdf-> matrix_width))
				dda_matrix_corner(fdf, x_val, y_val);
			else if ((y_val != 0 && y_val + 1 != fdf->matrix_height)
				&& (x_val != 0 && x_val + 1 != fdf->matrix_width))
				dda_matrix_inside(fdf, x_val, y_val);
			else
				dda_matrix_edge(fdf, x_val, y_val);
			x_val++;
		}
		y_val++;
	}
}

static void	dda_matrix_corner(t_app *fdf, int x_val, int y_val)
{

}

static void	dda_matrix_edge(t_app *fdf, int x_val, int y_val)
{

}

static void	dda_matrix_inside(t_app *fdf, int x_val, int y_val)
{

}
