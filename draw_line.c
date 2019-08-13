/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:38:21 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/13 13:31:13 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap_em(int *a0, int *a1)
{
	int c;

	c = *a0;
	*a0 = *a1;
	*a1 = c;
}

int 	steep_check(int *x0, int *x1, int *y0, int *y1)
{
	int	steep;

	steep = 0;
	if (labs(*y1 - *y0) > labs(*x1 - *x0))
	{
		steep = 1;
		swap_em(x0, y0);
		swap_em(x1, y1);
	}
	if (*x0 > *x1)
	{
		swap_em(x0, x1);
		swap_em(y0, y1);
	}
	return (steep);
}

void	draw_line(t_coords *line, t_window *window)
{
	int x0[1];
	int x1[1];
	int y0[1];
	int y1[1];
	int	dx;
	int	dy;
	int error;
	int x;
	int y;
	int ystep;
	unsigned int	final_color;
	int 	i;
	int 	steep;

	*x0 = line->x0;
	*x1 = line->x1;
	*y0 = line->y0;
	*y1 = line->y1;

	steep = steep_check(x0, x1, y0, y1);
	dx = *x1 - *x0;
	dy = labs(*y1 - *y0);
	error = dx/2;
	if (*y0 < *y1)
		ystep = 1;
	else if (*y0 > *y1)
		ystep = -1;
	y = *y0;
	x = *x0;
	while (x <= *x1)
	{
		final_color = get_color(x, line, steep);
		if ((x >= 0 && x <= MAP_W && y > 0 && y <= MAP_H - 300 && steep == 0) ||
				(y >= 0 && y <= MAP_W && x > 0 && x <= MAP_H - 300 && steep == 1))
		{
			i = find_i(x, y, window, steep);
			put_color(window->img_data, i, final_color);
		}
		error -= dy;
		if (error < 0)
		{
			y = y + ystep;
			error = error + dx;
		}
		x++;
	}
}

int 	find_i(int x, int y, t_window *window ,int steep)
{
	int i;

	if (steep == 0)
		i = (x  * (*window->depth / 8)) + (y * (*window->linesize));
	else
		i = (y * (*window->depth / 8)) + (x * (*window->linesize));
	return (i);
}

void	put_color(char *img_data, int i, unsigned int color)
{
	img_data[i] = color; // B — Blue
	img_data[++i] = color >> 8; // G — Green
	img_data[++i] = color >> 16; // R — Red
//	img_data[++i] = 0; // Alpha channel
}

double percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int get_light(unsigned int start, unsigned int end, double percentage)
{
	return ((unsigned int)((1 - percentage) * start + percentage * end));
}

unsigned int get_color(int cur_x, t_coords *line, int steep)
{
	unsigned int     red;
	unsigned int     green;
	unsigned int     blue;
	double  percentage;

	if (line->color_start == line->color_finish)
		return (line->color_start);
	if (steep == 0)
		percentage = percent(line->x0, line->x1, cur_x);
	else
		percentage = percent(line->y0, line->y1, cur_x);
	red = get_light((line->color_start >> 16) & 0xFF, (line->color_finish >> 16) & 0xFF, percentage);
	green = get_light((line->color_start >> 8) & 0xFF, (line->color_finish >> 8) & 0xFF, percentage);
	blue = get_light(line->color_start & 0xFF, line->color_finish & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
