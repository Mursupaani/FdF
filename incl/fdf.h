/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:52:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/17 14:36:32 by anpollan         ###   ########.fr       */
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
//WARN: Is it okay to use?
# include <X11/keysym.h>
# include <X11/X.h>
//WARN: Is it okay to use?
# include "mlx.h"
# include "mlx_int.h"
# include "../libft/libft.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

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
	int		**matrix;
	int		matrix_width;
	int		matrix_height;
	float	dda_scalar;
	float	projection_angle;
}	t_app;

typedef struct s_matrix
{
	int	**matrix;
	int	matrix_width;
	int	matrix_height;
}	t_matrix;

enum Error_types
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
enum Coordinate
{
	X,
	Y
}	;

//WARN: Remove
void	print_matrix(t_app *fdf);

void	start_fdf(t_app *fdf);
int		**parse_fdf_file(t_app *fdf);
void	free_memory(t_app *fdf);
void	exit_success(t_app *fdf);
void	exit_error(t_app *fdf, int error);
float	*calculate_destination_x_and_y(t_app *fdf, int x, int y);
void	dda(t_app *fdf);

#endif
