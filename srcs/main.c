/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:49:40 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/14 20:57:07 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_mlx	*initialize_mlx_display(void);
int				keypress_hook(int keycode, void *param);

int	main(int argc, char *argv[])
{
	t_mlx	*mlx;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx = initialize_mlx_display();
	mlx_pixel_put(mlx->mlx, mlx->mlx_win, 10, 10, 0x00FFFFFF);
	mlx_string_put(mlx->mlx, mlx->mlx_win, 100, 100, 0x00FF0000, "Testing");
	// mlx_put_image_to_window(mlx, mlx_win, img->img, 0,0);
	mlx_hook(mlx->mlx_win, KeyPress, KeyPressMask, keypress_hook, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;
//
// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

int	keypress_hook(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keycode == XK_Escape)
		exit_success(mlx);
	return (0);
}

static t_mlx	*initialize_mlx_display(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		exit_error(mlx);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_error(mlx);
	mlx->mlx_win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
	if (!mlx->mlx_win)
		exit_error(mlx);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!mlx->img)
		exit_error(mlx);
	mlx->img_pixels = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
	return (mlx);
}
