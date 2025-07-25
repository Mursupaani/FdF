/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:52:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 12:47:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include <float.h>
//WARN: Is it okay to use?
# include <X11/keysym.h>
# include <X11/X.h>
//WARN: Is it okay to use?
# include "mlx.h"
# include "mlx_int.h"
# include "../libft/libft.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_projection_pixel
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_pixel;

typedef struct s_app
{
	char	*file_path;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_pixels;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_width;
	int		screen_height;
	int		matrix_width;
	int		matrix_height;
	float	img_scalar;
	float	x_proj_angle;
	float	y_proj_angle;
	t_pixel	**world;
	t_pixel	**screen;
	float	z_scalar;
	int		x_centering_offset;
	int		y_centering_offset;
	int		x_move_view;
	int		y_move_view;
	float	proj_min_x;
	float	proj_max_x;
	float	proj_min_y;
	float	proj_max_y;
	int		default_color;
	int		line_ends[4];
}	t_app;

typedef struct s_matrix
{
	int	**matrix;
	int	matrix_width;
	int	matrix_height;
}	t_matrix;

typedef struct s_line_calculation
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
}	t_line_calc;

enum e_error_types
{
	MALLOC_ERR,
	FILETYPE_ERR,
	FD_ERR,
	FDF_STRUCT_ERR,
	MLX_INIT_ERR,
	MLX_WIN_ERR,
	MLX_IMG_ERR,
	MATRIX_ERR,
	PARSING_ERR,
	GET_NEXT_LINE_ERR
}	;

enum e_coordinate
{
	X,
	Y
}	;

enum e_line_end_points
{
	X0,
	Y0,
	X1,
	Y1
}	;

//WARN: Remove
void	print_matrix(t_app *fdf, t_pixel **space);
void	calculate_centering_offset(t_app *fdf);

void	start_fdf(t_app *fdf);
t_pixel	**parse_fdf_file(t_app *fdf);
t_pixel	**initialize_pixel_matrix(t_app *fdf);
void	save_pixel_coordinates(t_pixel **space, int x, int y, int z);
void	free_memory(t_app *fdf);
void	exit_success(t_app *fdf);
void	exit_error(t_app *fdf, int error);
void	calculate_projection_x_and_y(t_app *fdf, int x, int y);
void	draw_pixels_on_window(t_app *fdf);
void	pixel_to_image(t_app *fdf, int x, int y, int color);
void	calculate_bounding_box(t_app *fdf);
void	draw_pixel(t_app *fdf, int x, int y);
void	draw_lines_between_points(t_app *fdf);
void	reset_image(t_app *fdf);
void	update_image(t_app *fdf);
void	reset_view(t_app *fdf);
void	reset_view_settings(t_app *fdf);
void	change_color(t_app *fdf, int keycode);
int		mouse_hook(int button, int x, int y, void *param);
int		keypress_hook(int keycode, void *param);
float	deg_to_rad(float deg);
int		destroy_notify_hook(void *param);
void	move_view(t_app *fdf, int keycode);
void	zoom_view(t_app *fdf, int keycode);
void	rotate_up_down(t_app *fdf, int keycode);
void	change_z_depth(t_app *fdf, int keycode);
void	count_matrix_width(t_app *fdf, char *line);
int		count_matrix_dimensions(t_app *fdf);

#endif
