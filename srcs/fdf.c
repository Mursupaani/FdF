/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:42:13 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/15 19:31:09 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fdf.h"

void	start_fdf(t_app *fdf)
{
	fdf->matrix = parse_fdf_file(fdf);
	if (!fdf->matrix)
		exit_error(fdf, MALLOC_ERR);
}
