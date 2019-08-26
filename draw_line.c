/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:38:21 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/26 13:05:36 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				*steep_check(int *x0, int *x1, int *y0, int *y1)
{
	int	*steep;

	steep = (int*)malloc(sizeof(int) * 2);
	steep[0] = 0;
	steep[1] = 0;
	if (labs(*y1 - *y0) > labs(*x1 - *x0))
	{
		steep[0]++;
		ft_swap(x0, y0);
		ft_swap(x1, y1);
	}
	if (*x0 > *x1)
	{
		steep[1]++;
		ft_swap(x0, x1);
		ft_swap(y0, y1);
	}
	return (steep);
}

void				pre_draw_line(int coord[4], t_coords *line)
{
	coord[0] = line->x0;
	coord[1] = line->x1;
	coord[2] = line->y0;
	coord[3] = line->y1;
}

void				inter_via_mass(int coord[4], int incr[4])
{
	incr[0] = coord[1] - coord[0];
	incr[1] = labs(coord[3] - coord[2]);
	incr[2] = incr[0] / 2;
	incr[3] = 1;
	coord[2] < coord[3] ? (incr[3] = 1) : (incr[3] *= -1);
}

int 				check_shit(int ixy[3], int *steep)
{
	return (
	(((ixy[1] >= 0 && ixy[1] <= MAP_W && ixy[2] > 0
	&& ixy[2] <= MAP_H - 300 && steep[0] == 0)
	|| (ixy[2] >= 0 && ixy[2] <= MAP_W && ixy[1] > 0
	&& ixy[1] <= MAP_H - 300 && steep[0] == 1))) ? 0 : 1);
}

void finish_count(int ixy[3], int incr[4])
{
	incr[2] -= incr[1];
	if (incr[2] < 0)
	{
		ixy[2] = ixy[2] + incr[3];
		incr[2] = incr[2] + incr[0];
	}
}

/* coord[4] - координаты начала и конца линии */
/* приращение по х - incr[0] и по у - incr[1];  */
/* incr[2] - ошибка; incr[3] - шаг по y */

void				draw_line(t_coords *line, t_window *window)
{
	int				coord[4];
	int				incr[4];
	int				ixy[3];
	unsigned int	final_color;
	int				*steep;

	if (window->gradient_mod == 1)
		recolor_line(line, window);
	else
		recolor_back(line, window);
	pre_draw_line(coord, line);
	steep = steep_check(&coord[0], &coord[1], &coord[2], &coord[3]);
	inter_via_mass(coord, incr);
	ixy[2] = coord[2];
	ixy[1] = coord[0];
	while (ixy[1]++ <= coord[1])
	{
//		if (window->gradient_mod == 0)
			final_color = get_color(ixy[1], line, steep);
//		else if (window->gradient_mod == 1)
	//
			//		final_color = get_color_z(ixy, line, steep/*, window*/);
		if (!check_shit(ixy, steep))
		{
			ixy[0] = find_i(ixy[1], ixy[2], window, steep);
			put_color(window->img_data, ixy[0], final_color);
		}
		finish_count(ixy, incr);
	}
	free(steep);
}

int			find_i(int x, int y, t_window *window, int *steep)
{
	int i;

	if (steep[0] == 0)
		i = (x * (*window->depth / 8)) + (y * (*window->linesize));
	else
		i = (y * (*window->depth / 8)) + (x * (*window->linesize));
	return (i);
}

void			put_color(char *img_data, int i, unsigned int color)
{
	img_data[i] = color;
	img_data[++i] = color >> 8;
	img_data[++i] = color >> 16;
}

double			percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int				get_light(unsigned int start, unsigned int end, double percent)
{
	return ((unsigned int)((1 - percent) * start + percent * end));
}

unsigned int	get_color(int cur_x, t_coords *line, int *steep)
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
	red = get_light((line->color_start >> 16) & 0xFF, (line->color_finish >> 16)
	& 0xFF, percentage);
	green = get_light((line->color_start >> 8) & 0xFF, (line->color_finish >> 8)
	& 0xFF, percentage);
	blue = get_light(line->color_start & 0xFF, line->color_finish
	& 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

/*unsigned int	get_color_z(int ixy[3], t_coords *line, int *steep, t_window *window)
{
	unsigned int	color;

//	if (line->color_start == line->color_finish)
//		return (line->color_start);
//	if (line->z0 == line->z1 && line->z0 == window->map->z_min)
//		return (window->color[0]);
//	if (line->z0 == line->z1 && line->z0 == window->map->z_max)
//		return (window->color[1]);
	color = get_color(ixy[1], line, steep);
	return (color);
}*/

void	recolor_line(t_coords *line, t_window *window)
{
  //	if (!color_start_flag)
		line->color_start = color_for_z(line->z0, line, window);
//	if (!color_finish_flag)
		line->color_finish = color_for_z(line->z1, line, window);
//		if (line->z0 != line->z1 && line->color_finish == line->color_start)
//			printf ("FUCK!\n");
}

void	recolor_back(t_coords *line, t_window *window)
{
	//	if (!color_start_flag)
		line->color_start = window->color[0];
		//if (!color_finish_flag)
		line->color_finish = window->color[1];
}

unsigned int	color_for_z(int z, t_coords *line, t_window *window)
{
	double			percentage;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	if (z == window->map->z_min)
		return (window->color[0]);
	else if (z == window->map->z_max)
		return (window->color[1]);
	percentage = percent(window->map->z_min, window->map->z_max, z);
	t_coords *go = line;
	go = go->next;
	red = get_light((window->color[0] >> 16) & 0xFF, (window->color[1] >> 16)
													  & 0xFF, percentage);
	green = get_light((window->color[0] >> 8) & 0xFF, (window->color[1] >> 8)
													   & 0xFF, percentage);
	blue = get_light(window->color[0] & 0xFF, window->color[1]
											   & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
