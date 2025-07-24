/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:49:40 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 10:17:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_app	*initialize_app(char *file_path);
static bool		is_fdf_file(const char *filename);
static void		initialize_hooks(t_app *fdf);

//WARN: Delete me
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
	draw_pixels_on_window(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
	exit_success(fdf);
	return (0);
}

void	pixel_to_image(t_app *fdf, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < WIN_WIDTH && x >= 0 && y < WIN_HEIGHT && y >= 0)
	{
		offset = (x * (fdf->bits_per_pixel / 8)) + (y * fdf->line_length);
		pixel = fdf->img_pixels + offset;
		*(int *)pixel = color;
	}
}

static t_app	*initialize_app(char *file_path)
{
	t_app	*fdf;

	fdf = (t_app *)ft_calloc(1, sizeof(t_app));
	if (!fdf)
		exit_error(fdf, FDF_STRUCT_ERR);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_error(fdf, MLX_INIT_ERR);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->mlx_win)
		exit_error(fdf, MLX_WIN_ERR);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	fdf->file_path = file_path;
	fdf->world = NULL;
	fdf->screen = NULL;
	fdf->matrix_height = 0;
	fdf->matrix_width = 0;
	fdf->default_color = 0xFFFFFF;
	reset_view_settings(fdf);
	initialize_hooks(fdf);
	return (fdf);
}

void	reset_view_settings(t_app *fdf)
{
	fdf->img_scalar = 10.0f;
	fdf->z_scalar = 0.1f;
	fdf->x_centering_offset = 0;
	fdf->y_centering_offset = 0;
	fdf->x_move_view = 0;
	fdf->y_move_view = 0;
	fdf->x_proj_angle = 40.0f;
	fdf->y_proj_angle = 40.0f;
	fdf->proj_min_x = FLT_MAX;
	fdf->proj_max_x = FLT_MIN;
	fdf->proj_min_y = FLT_MAX;
	fdf->proj_max_y = FLT_MIN;
	fdf->default_color = 0xFFFFFF;
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

static void	initialize_hooks(t_app *fdf)
{
	mlx_key_hook(fdf->mlx_win, keypress_hook, fdf);
	mlx_mouse_hook(fdf->mlx_win, mouse_hook, fdf);
	mlx_hook(fdf->mlx_win, DestroyNotify, 0, destroy_notify_hook, fdf);
}
