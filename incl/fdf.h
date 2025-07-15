/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:52:36 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/14 20:54:54 by anpollan         ###   ########.fr       */
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

// typedef struct	s_data
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_pixels;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		screen_width;
	int		screen_height;
}	t_mlx;

void	free_memory(t_mlx *mlx);
void	exit_success(t_mlx *mlx);
void	exit_error(t_mlx *mlx);

#endif
