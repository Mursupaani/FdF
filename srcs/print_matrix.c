#include "../incl/fdf.h"

void	print_matrix(t_app *fdf, t_pixel **space)
{
	int i;
	int j;

	ft_printf("Matrix width in fdf file: %d\n", fdf->matrix_width);
	ft_printf("Matrix height in fdf file: %d\n", fdf->matrix_height);
	i = 0;
	while (i < fdf->matrix_height)
	{
		j = 0;
		while (j < fdf->matrix_width)
		{
			ft_printf("%d", (int)space[i][j].z);
			if (space[i][j].z < 10)
				ft_printf("  ");
			else
				ft_printf(" ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
