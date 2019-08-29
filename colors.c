/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:45:35 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/29 22:49:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				put_color(char *img_data, int i, unsigned int color)
{
	img_data[i] = color;
	img_data[++i] = color >> 8;
	img_data[++i] = color >> 16;
}

double				percent(int start, int end, int current)
{
	double			placement;
	double			distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int					light(unsigned int c1, unsigned int c2, double percent)
{
	return ((unsigned int)((1 - percent) * c1 + percent * c2));
}

unsigned int		get_color(int cur_x, t_coords *line, int *steep)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	double			percentage;

	if (line->color_start == line->color_finish)
		return (line->color_start);
	if (steep[0] == 0)
		percentage = percent(line->x0, line->x1, cur_x);
	else
		percentage = percent(line->y0, line->y1, cur_x);
	red = light((line->color_start >> 16) & 0xFF,
			(line->color_finish >> 16) & 0xFF, percentage);
	green = light((line->color_start >> 8) & 0xFF,
			(line->color_finish >> 8) & 0xFF, percentage);
	blue = light(line->color_start & 0xFF,
			line->color_finish & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
