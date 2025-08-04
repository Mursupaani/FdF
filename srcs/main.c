/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:49:40 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 12:05:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

static t_app	*initialize_app(char *file_path);
static bool		is_fdf_file(const char *filename);
static void		initialize_mlx(t_app *fdf);

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
	parse_fdf_file(fdf);
	draw_pixels_on_image(fdf);
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
	initialize_mlx(fdf);
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

static void	initialize_mlx(t_app *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit_error(fdf, MLX_INIT_ERR);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->mlx_win)
		exit_error(fdf, MLX_WIN_ERR);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
		exit_error(fdf, MLX_IMG_ERR);
	fdf->img_pixels = mlx_get_data_addr(
			fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	if (!fdf->img_pixels)
		exit_error(fdf, MLX_IMG_ERR);
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
