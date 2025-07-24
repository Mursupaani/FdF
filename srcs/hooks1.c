/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:59:10 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 10:31:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (button == 4)
	{
		fdf->img_scalar += 1.0f;
		update_image(fdf);
	}
	if (button == 5)
	{
		if (fdf->img_scalar <= 1.0f)
			return (0);
		fdf->img_scalar -= 1.0f;
		update_image(fdf);
	}
	(void)x;
	(void)y;
	return (0);
}

int	destroy_notify_hook(void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	exit_success(fdf);
	return (0);
}

int	keypress_hook(int keycode, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (keycode == XK_Escape)
		exit_success(fdf);
	if (keycode == XK_w)
	{
		fdf->z_scalar += 0.1f;
		update_image(fdf);
	}
	if (keycode == XK_q)
	{
		fdf->z_scalar -= 0.1f;
		update_image(fdf);
	}
	if (keycode == XK_r)
		reset_view(fdf);
	if (keycode == XK_Up)
	{
		fdf->y_move_view -= 20;
		update_image(fdf);
	}
	if (keycode == XK_Down)
	{
		fdf->y_move_view += 20;
		update_image(fdf);
	}
	if (keycode == XK_Left)
	{
		fdf->x_move_view -= 20;
		update_image(fdf);
	}
	if (keycode == XK_Right)
	{
		fdf->x_move_view += 20;
		update_image(fdf);
	}
	if (keycode == XK_c)
	{
		fdf->y_proj_angle -= 5;
		update_image(fdf);
	}
	if (keycode == XK_v)
	{
		fdf->y_proj_angle += 5;
		update_image(fdf);
	}
	if (keycode == XK_z)
	{
		change_color(fdf, '+');
		update_image(fdf);
	}
	if (keycode == XK_x)
	{
		change_color(fdf, '-');
		update_image(fdf);
	}
	return (0);
}
