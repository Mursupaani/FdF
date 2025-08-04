/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 10:49:56 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 12:05:32 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	move_view(t_app *fdf, int keycode)
{
	if (keycode == XK_Up)
		fdf->y_move_view += 20;
	if (keycode == XK_Down)
		fdf->y_move_view -= 20;
	if (keycode == XK_Left)
		fdf->x_move_view += 20;
	if (keycode == XK_Right)
		fdf->x_move_view -= 20;
	update_image(fdf);
}

void	change_color(t_app *fdf, int keycode)
{
	static int	i;
	int			colors[8];

	colors[0] = 0xFFFFFF;
	colors[1] = 0x065535;
	colors[2] = 0xffc0cb;
	colors[3] = 0x008080;
	colors[4] = 0xe6e6fa;
	colors[5] = 0xffa500;
	colors[6] = 0xd3ffce;
	colors[7] = 0x003366;
	if (keycode == XK_x)
		i++;
	if (keycode == XK_z)
		i--;
	if (i < 0)
		i = 7;
	if (i > 7)
		i = 0;
	fdf->default_color = colors[i];
	update_image(fdf);
}

void	rotate_up_down(t_app *fdf, int keycode)
{
	if (keycode == XK_c)
		fdf->y_proj_angle -= 5;
	if (keycode == XK_v)
		fdf->y_proj_angle += 5;
	update_image(fdf);
}

void	reset_view_settings(t_app *fdf)
{
	fdf->img_scalar = 10.0f;
	fdf->z_scalar = 0.1f;
	fdf->x_centering_offset = 0;
	fdf->y_centering_offset = 0;
	fdf->x_move_view = 0;
	fdf->y_move_view = 0;
	fdf->x_proj_angle = 30.0f;
	fdf->y_proj_angle = 30.0f;
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
	fdf->default_color = 0xFFFFFF;
}

void	change_z_depth(t_app *fdf, int keycode)
{
	if (keycode == XK_w)
		fdf->z_scalar += 0.1f;
	if (keycode == XK_q)
		fdf->z_scalar -= 0.1f;
	update_image(fdf);
}
