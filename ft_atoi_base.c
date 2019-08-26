/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:03:05 by samymone          #+#    #+#             */
/*   Updated: 2019/08/24 15:03:10 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			diffspaces(const char *str)
{
	if (*str == '\n' || *str == ' ' || *str == '\r' || *str == '\t' ||
		*str == '\f' || *str == '\v')
		return (1);
	return (0);
}

int					get_value(int a, int i)
{
	int r;
	int hex;

	hex = 1;
	while (i-- > 0)
		hex *= 16;
	r = ft_atoi(ft_itoa(a));
	return (r * hex);
}

unsigned int		ft_atoi_base(char *str)
{
	unsigned int	res;
	int				len;
	int				i;
	char			*new;

	res = 0;
	i = 0;
	while (diffspaces(str) == 1)
		str++;
	len = ft_strlen(str) - 1;
	if (!(new = (char*)malloc(sizeof(char) * i)))
		return (0);
	new = str;
	while (len > -1)
	{
		if (new[len] >= '0' && new[len] <= '9')
			res += get_value(new[len] - 48, i);
		else if (new[len] >= 'a' && new[len] <= 'f')
			res += get_value(new[len] - 87, i);
		else if (new[len] >= 'A' && new[len] <= 'F')
			res += get_value(new[len] - 55, i);
		i++;
		len--;
	}
	return (res);
}