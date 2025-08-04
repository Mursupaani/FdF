/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:59:10 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 11:08:01 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	initialize_hooks(t_app *fdf)
{
	mlx_key_hook(fdf->mlx_win, keypress_hook, fdf);
	mlx_mouse_hook(fdf->mlx_win, mouse_hook, fdf);
	mlx_hook(fdf->mlx_win, DestroyNotify, 0, destroy_notify_hook, fdf);
}

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
	if (keycode == XK_r)
		reset_view(fdf);
	if (keycode == XK_w || keycode == XK_q)
		change_z_depth(fdf, keycode);
	if (keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_Left || keycode == XK_Right)
		move_view(fdf, keycode);
	if (keycode == XK_c || keycode == XK_v)
		rotate_up_down(fdf, keycode);
	if (keycode == XK_z || keycode == XK_x)
		change_color(fdf, keycode);
	return (0);
}
