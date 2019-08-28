/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/28 15:10:18 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
///ТУТ ВСЕ ПРОСТО, ПОКА НЕ ЗАКОНЧАТСЯ ЭЛЕМЕНТЫ СТРУКТУРЫ t_coords, будет к каждому запускать DRAW_LINE
int	draw_map(t_coords *lines, t_window *window)
{

	t_coords	*go;

	go = lines;
	if (window->gradient_mod == 1)
		find_max_min_z(go, window);
	recolor_map(go, window);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	while (go != NULL)
	{
		draw_line(go, window);
		go = go->next;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);//MLX ФУНКЦИЯ, КОТОРАЯ КИДАЕТ ИЗОБРАЖЕНИЕ НА ЭКРАН
	return (0);
}

void	recolor_map(t_coords *lines, t_window *window)
{
	t_coords *go;
	t_coords *start;

	start = window->lines;
	go = lines;
	if (window->gradient_mod == 1)
	{
		while (go != NULL)
		{
			recolor_line(go, window, start);
			go = go->next;
			start = start->next;
		}
	}
	else
	{
		while (go != NULL)
		{
			recolor_back(go, window, start);
			go = go->next;
			start = start->next;
		}
	}
}

void	recolor_line(t_coords *line, t_window *window, t_coords *start)
{
	if (!start->color_flag_start)
		line->color_start = color_for_z(line->z0/*, line*/, window, start);
	else
		line->color_start = start->color_start;
	if (!start->color_flag_finish)
		line->color_finish = color_for_z(line->z1,/* line, */window, start);
	else
		line->color_finish = start->color_finish;
}

void	recolor_back(t_coords *line, t_window *window, t_coords *start)
{
	if (!start->color_flag_start)
		line->color_start = window->color[0];
	else
		line->color_start = start->color_start;
	if (!start->color_flag_finish)
		line->color_finish = window->color[1];
	else
		line->color_finish = start->color_finish;
}

unsigned int	color_for_z(int z/*, t_coords *line*/, t_window *window, t_coords *start)
{
	double			percentage;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	fixed_z0;
	unsigned int	fixed_z1;
////////ЕСЛИ ЕСТЬ ЦВЕТ ТОЧКИ ТО СЧИТАТЬ РГБ С НЕЙ А ЕСЛИ НЕТ ТО С ВИНДОУ0 ИЛИ ВИНДОУ ТАМ 1 НУ ПО СИТУАЦИИ КОРОЧЕ


	if (z == window->map->z_min)
		return (window->color[0]);
	else if (z == window->map->z_max)
		return (window->color[1]);
	if (!start->color_flag_start)
		fixed_z0 = window->color[0];
	else
		fixed_z0 = start->color_start;
	if (!start->color_flag_finish)
		fixed_z1 = window->color[1];
	else
		fixed_z1 = start->color_finish;
	percentage = percent(window->map->z_min, window->map->z_max, z);
/*	red = get_light((window->color[0] >> 16) & 0xFF, (window->color[1] >> 16)
													 & 0xFF, percentage);
	green = get_light((window->color[0] >> 8) & 0xFF, (window->color[1] >> 8)
													  & 0xFF, percentage);
	blue = get_light(window->color[0] & 0xFF, window->color[1]
											  & 0xFF, percentage);*/
	red = get_light((fixed_z0 >> 16) & 0xFF, (fixed_z1 >> 16)
													 & 0xFF, percentage);
	green = get_light((fixed_z0 >> 8) & 0xFF, (fixed_z1 >> 8)
													  & 0xFF, percentage);
	blue = get_light(fixed_z0 & 0xFF, fixed_z1
											  & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}