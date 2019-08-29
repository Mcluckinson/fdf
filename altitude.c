/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altitude.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:15:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/29 16:03:03 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_altitude(int key, t_window *window)
{
	t_coords	*go;

	if (window->projection == 1)
		return ;
	go = window->lines;
	if (key == 1)
		window->height_mod -=10;
	else if (key == 13)
		window->height_mod +=10;
	while (go != NULL)
	{
		if (go->z1orig != 0)
			go->z1 = go->z1orig + window->height_mod;
		if (go->z0orig != 0)
			go->z0 = go->z0orig + window->height_mod;
		go = go->next;
	}
	redraw_altitude(window);
	window->current = fix_orig(window->current, window->fix_ratio);
	fix_current(window->current, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
}
////СМЕШНАЯ ФУНКЦИЯ КОТОРАЯ КИДАЕТ СЛУЧАЙНЫЕ ЦВЕТА
void	randomise_colors(t_window *window)
{
	t_coords *go;

	go = window->current;
	while (go != NULL)
	{
		go->color_finish = rand();
		go->color_start = rand();
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
//////МЕНЯЕМ КООРДИНАТЫ Х и У для изометрии, т.к они зависят от высоты
void	redraw_altitude(t_window *window)
{
	t_coords	*orig;
	t_coords	*go;

	orig = window->lines;
	go = window->current;

	while (orig != NULL)
	{
		//go->v1 = vector_upgrade(orig->v1)
		//go->v2 = vector_upgrade(orig->v2)
		go->x0 = (orig->x0 - orig->y0)  * cos(0.523599);
		go->x1 = (orig->x1 - orig->y1)  * cos(0.523599);
		go->y0 = (orig->z0) * -1 + ((orig->x0 + orig->y0)  * sin(0.523599));
		go->y1 = (orig->z1) * -1 + ((orig->x1 + orig->y1)  * sin(0.523599));
		go->z0 = orig->z0;
		go->z1 = orig->z1;
		orig = orig->next;
		go = go->next;
	}
}