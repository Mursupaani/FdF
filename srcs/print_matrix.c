#include "../incl/fdf.h"

void	print_matrix(t_app *fdf)
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
			ft_printf("%d", fdf->world_space[i][j].z);
			if (fdf->world_space[i][j].z == 0)
				ft_printf("  ");
			else
				ft_printf(" ");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
