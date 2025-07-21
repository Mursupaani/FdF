/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:27:45 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 14:35:26 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static void	dda_matrix_corner(t_app *fdf, int x, int y);
// static void	dda_matrix_edge(t_app *fdf, int x, int y);
// static void	dda_matrix_inside(t_app *fdf, int x, int y);

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
			dda_matrix_corner(fdf, x, y);
			// if ((y == 0 || y == fdf->matrix_height)
			// && (x == 0 || x == fdf-> matrix_width))
			// 	dda_matrix_corner(fdf, x, y);
			// else if ((y != 0 && y != fdf->matrix_height)
			// 	&& (x != 0 && x != fdf->matrix_width))
			// 	dda_matrix_inside(fdf, x, y);
			// else
			// 	dda_matrix_edge(fdf, x, y);
			x++;
		}
		y++;
	}
}

static void	dda_matrix_corner(t_app *fdf, int x, int y)
{
	float	*c1;
	float	*c2;
	float	dx;
	float	dy;

	c1 = calculate_destination_x_and_y(fdf, x, y);
	c2 = calculate_destination_x_and_y(fdf, x + 1, y + 1);
	dx = c2[X] - c1[X];
	dy = c2[Y] - c1[Y];
	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, x, y, 0x00FFFFFF);
	ft_printf("x: %d\ty: %d\tz: %d\n", (int)c1[X], (int)c1[Y], fdf->matrix[y][x]);
		pixel_to_image(fdf, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
	// pixel_to_image(fdf, x * 10, y * 10, 0x00FFFFFF);
	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
	free(c1);
	free(c2);
	(void)dx;
	(void)dy;
}
//
// static void	dda_matrix_edge(t_app *fdf, int x, int y)
// {
// 	float	*c1;
// 	float	*c2;
// 	float	dx;
// 	float	dy;
//
// 	c1 = calculate_destination_x_and_y(fdf, x, y);
// 	c2 = calculate_destination_x_and_y(fdf, x + 1, y + 1);
// 	dx = c2[X] - c1[X];
// 	dy = c2[Y] - c1[Y];
// 	ft_printf("x: %d\ty: %d\tz: %d\n", (int)c1[X], (int)c1[Y], fdf->matrix[y][x]);
// 	pixel_to_image(fdf, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
// 	// pixel_to_image(fdf, x * 10, y * 10, 0x00FFFFFF);
// 	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
// 	// my_mlx_pixel_put(fdf, fabs(c1[X]), fabs(c1[Y]), 0x00FFFFFF);
// 	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, x, y, 0x00FFFFFF);
// 	free(c1);
// 	free(c2);
// 	(void)dx;
// 	(void)dy;
// }
//
// static void	dda_matrix_inside(t_app *fdf, int x, int y)
// {
// float	*c1;
// 	float	*c2;
// 	float	dx;
// 	float	dy;
//
// 	c1 = calculate_destination_x_and_y(fdf, x, y);
// 	c2 = calculate_destination_x_and_y(fdf, x + 1, y + 1);
// 	dx = c2[X] - c1[X];
// 	dy = c2[Y] - c1[Y];
// 	ft_printf("x: %d\ty: %d\tz: %d\n", (int)c1[X], (int)c1[Y], fdf->matrix[y][x]);
// 	pixel_to_image(fdf, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
// 	// pixel_to_image(fdf, x * 10, y * 10, 0x00FFFFFF);
// 	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, (int)(c1[X] * fdf->dda_scalar), (int)(c1[Y] * fdf->dda_scalar), 0x00FFFFFF);
// 	// my_mlx_pixel_put(fdf, fabs(c1[X]), fabs(c1[Y]), 0x00FFFFFF);
// 	// mlx_pixel_put(fdf->mlx, fdf->mlx_win, x, y, 0x00FFFFFF);
// 	free(c1);
// 	free(c2);
// 	(void)dx;
// 	(void)dy;
// }
