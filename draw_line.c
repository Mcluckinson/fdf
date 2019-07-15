/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:38:21 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/13 19:29:14 by cyuriko          ###   ########.fr       */
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
	int 	color;
	int 	i;
	int 	steep;

	*x0 = line->x0;
	*x1 = line->x1;
	*y0 = line->y0;
	*y1 = line->y1;
	color = 0x00ff00ff;
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
		i = find_i(x, y, window, steep);
		window->img_data = put_color(window->img_data, i, color);
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
		i = (x * (*window->depth / 8)) + (y * (*window->linesize));
	else
		i = (y * (*window->depth / 8)) + (x * (*window->linesize));
	return (i);
}

char *put_color(char *img_data, int i, int color)
{
	img_data[i] = color; // B — Blue
	img_data[++i] = color >> 8; // G — Green
	img_data[++i] = color >> 16; // R — Red
	img_data[++i] = 0; // Alpha channel
	return (img_data);
}
/*
int main ()
{
	t_window	*window;

	window = (t_window*)malloc(sizeof(t_window));
	int 	x0[1];
	int 	x1[1];
	int 	y0[1];
	int 	y1[1];

	window->img_ptr = mlx_new_image(window->mlx_ptr, 800, 800);
	window->linesize = (int*)malloc(sizeof(int));
	window->linesize = 800 * UNIQ_BPP;
	window->depth = (int*)malloc(sizeof(int));
	window->depth = UNIQ_BPP * 8;
	window->endian = 0;
	window->mlx_ptr = mlx_init();
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->linesize);
	window->win_ptr = mlx_new_window(window->mlx_ptr, 800, 800, "FDF");
	*x0 = 0;
	*y0 = 10;
	*x1 = 50;
	*y1 = 70;
	draw_line(x0, x1,y0,y1, img_data, depth,linesize);
	*x0 = 100;
	*y0 = 10;
	*x1 = 350;
	*y1 = 10;
	draw_line(x0, x1,y0,y1, img_data, depth,linesize);

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 400);
	mlx_loop(mlx_ptr);
	return (0);
}
*/