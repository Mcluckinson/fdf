/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:03:05 by samymone          #+#    #+#             */
/*   Updated: 2019/08/27 15:32:04 by cyuriko          ###   ########.fr       */
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
///////////////ЭТО ЧТО ТАМ МАЛЛОК НЕЗАФРИШЕННЫЙ????
///////////////NEW = STR?????
//////////////НЕЛЬЗЯ СРАЗУ ПО STR ИДТИ, ЗАЧЕМ NEW????
////////////Я НЕ ОРУ, У МЕНЯ ПРОСТО ЦВЕТ КОММЕНТОВ ХУЕВЫЙ, ТАК ВИДНО ЛУЧШЕ
unsigned int		ft_atoi_base(char *str)
{
	unsigned int	res;
	int				len;
	int				i;
//	char			*new;

	res = 0;
	i = 0;
	while (diffspaces(str) == 1)
		str++;
	len = ft_strlen(str) - 1;
//	if (!(new = (char*)malloc(sizeof(char) * i)))
//		return (0);
//	new = str;
	while (len > -1)
	{
		if (str[len] >= '0' && str[len] <= '9')
			res += get_value(str[len] - 48, i);
		else if (str[len] >= 'a' && str[len] <= 'f')
			res += get_value(str[len] - 87, i);
		else if (str[len] >= 'A' && str[len] <= 'F')
			res += get_value(str[len] - 55, i);
		i++;
		len--;
	}
	return (res);
}
