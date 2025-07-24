/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hexadecimal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:24:39 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/24 15:18:29 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nptr_to_lower(const char *nptr, char *nbr_str, int nptrlen);
static int	convert_hexadecimal_to_nbr(char *nbr_str, long *nbr, int nptrlen);
static int	convert_single_hex_to_int(char hex);

int	*ft_atoi_hexadecimal_safe(const char *nptr)
{
	static long	nbr[1];
	char		*nbr_str;
	int			nptrlen;

	if (ft_strncmp(nptr, "0x", 2))
		return (NULL);
	nptr += 2;
	nptrlen = ft_strlen(nptr);
	if (nptrlen == 0)
		return (NULL);
	nbr_str = (char *)malloc(nptrlen + 1);
	if (!nbr_str)
		return (NULL);
	nbr_str = nptr_to_lower(nptr, nbr_str, nptrlen);
	if (!convert_hexadecimal_to_nbr(nbr_str, nbr, nptrlen))
		return (NULL);
	return ((int *)nbr);
}

static char	*nptr_to_lower(const char *nptr, char *nbr_str, int nptrlen)
{
	int	i;

	i = 0;
	while (i <= nptrlen)
	{
		nbr_str[i] = nptr[i];
		i++;
	}
	i = 0;
	while (i < nptrlen)
	{
		nbr_str[i] = ft_tolower(nbr_str[i]);
		i++;
	}
	return (nbr_str);
}

static int	convert_hexadecimal_to_nbr(char *nbr_str, long *nbr, int nptrlen)
{
	int			i;
	int			hex;

	i = 0;
	while (i < nptrlen)
	{
		*nbr *= 16;
		hex = convert_single_hex_to_int(nbr_str[i]);
		if (hex == -1)
			return (false);
		*nbr += hex;
		i++;
	}
	return (true);
}

static int	convert_single_hex_to_int(char hex)
{
	const char	*base = "0123456789abcdef";
	int			i;

	i = 0;
	if (hex == '\n')
		return (0);
	while (base[i])
	{
		if (hex == base[i])
			return (i);
		i++;
	}
	return (-1);
}
