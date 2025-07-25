/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 17:44:15 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_atoi_safe(const char *nptr)
{
	static long int	res[1];
	int				sign;

	sign = 1;
	*res = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
		if (!ft_isdigit(*nptr))
			return (NULL);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		*res *= 10;
		*res += *nptr - '0';
		nptr++;
	}
	*res *= sign;
	if (*res <= INT_MAX && *res >= INT_MIN && (*nptr == '\0' || *nptr == '\n'))
		return ((int *)res);
	return (NULL);
}
