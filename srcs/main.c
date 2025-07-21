/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:49:40 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 14:36:44 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_app	*initialize_app(char *file_path);
static bool		is_fdf_file(const char *filename);
static int		destroy_notify_hook(void *param);
static int		keypress_hook(int keycode, void *param);
static void		initialize_hooks(t_app *fdf);

void	*test_malloc(void)
{
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_app	*fdf;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	if (!is_fdf_file(argv[1]))
		exit_error(NULL, FILETYPE_ERR);
	fdf = initialize_app(argv[1]);
	if (!fdf)
		exit_error(fdf, FDF_STRUCT_ERR);
	start_fdf(fdf);
	dda(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	// print_matrix(fdf);
	exit_success(fdf);
	return (0);
}

void	pixel_to_image(t_app *fdf, int x, int y, int color)
{
	char	*pixel;
	int		offset;
	
	if (x < SCREEN_WIDTH && x >= 0 && y < SCREEN_HEIGHT && y >= 0)
	{
		offset = (x * (fdf->bits_per_pixel / 8)) + (y * fdf->line_length);
		pixel = fdf->img_pixels + offset;
		*(int *)pixel = color;
	}
}

int	keypress_hook(int keycode, void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	if (keycode == XK_Escape)
		exit_success(fdf);
	return (0);
}

int	destroy_notify_hook(void *param)
{
	t_app	*fdf;

	fdf = (t_app *)param;
	exit_success(fdf);
	return (0);
}

static t_app	*initialize_app(char *file_path)
{
	t_app	*fdf;

	fdf = (t_app *)malloc(sizeof(t_app));
	if (!fdf)
		exit_error(fdf, FDF_STRUCT_ERR);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_error(fdf, MLX_INIT_ERR);
	fdf->mlx_win = mlx_new_window(fdf->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "FdF");
	if (!fdf->mlx_win)
		exit_error(fdf, MLX_WIN_ERR);
	fdf->img = mlx_new_image(fdf->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	fdf->file_path = file_path;
	fdf->matrix = NULL;
	fdf->matrix_height = 0;
	fdf->matrix_width = 0;
	fdf->dda_scalar =  15.0f;
	fdf->tile_width = 10;
	fdf->tile_height = 10;
	fdf->projection_angle = 0.0f;
	initialize_hooks(fdf);
	return (fdf);
}

static bool	is_fdf_file(const char *filename)
{
	int	strlen;

	strlen = ft_strlen(filename);
	if (strlen < 4)
		return (false);
	if (!ft_strncmp(filename + strlen - 4, ".fdf", 4))
		return (true);
	else
		return (false);
}

static void		initialize_hooks(t_app *fdf)
{
	mlx_hook(fdf->mlx_win, KeyPress, KeyPressMask, keypress_hook, fdf);
	mlx_hook(fdf->mlx_win, DestroyNotify, 0, destroy_notify_hook, fdf);
}
