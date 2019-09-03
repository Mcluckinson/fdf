/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altitude.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:15:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/03 15:47:08 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_altitude(int key, t_window *window)
{
	if (window->projection == 1)
		return ;
	if (key == 1)
		window->height_mod -= 10;
	else if (key == 13)
		window->height_mod += 10;
	fix_altitude(window);
	redraw_altitude(window->current, window);
	window->current = fix_orig(window->current, window->fix_ratio);
	fix(window->current, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
}

void	fix_altitude(t_window *window)
{
	t_coords	*go;

	go = window->lines;
	while (go != NULL)
	{
		if (go->z1orig != 0)
			go->z1 = go->z1orig + window->height_mod;
		if (go->z0orig != 0)
			go->z0 = go->z0orig + window->height_mod;
		go = go->next;
	}
}

void	redraw_altitude(t_coords *lines, t_window *window)
{
	t_coords	*orig;
	t_coords	*go;

	orig = window->lines;
	go = lines;
	while (orig != NULL)
	{
		go->x0 = (orig->x0 - orig->y0) * cos(0.523599);
		go->x1 = (orig->x1 - orig->y1) * cos(0.523599);
		go->y0 = (orig->z0) * -1 + ((orig->x0 + orig->y0) * sin(0.523599));
		go->y1 = (orig->z1) * -1 + ((orig->x1 + orig->y1) * sin(0.523599));
		go->z0 = orig->z0;
		go->z1 = orig->z1;
		orig = orig->next;
		go = go->next;
	}
}

void	find_max_min_z(t_coords *lines, t_window *window)
{
	t_coords *go;

	go = lines;
	window->map->z_min = go->z0;
	window->map->z_max = go->z0;
	while (go != NULL)
	{
		if (go->z0 < window->map->z_min)
			window->map->z_min = go->z0;
		if (go->z1 < window->map->z_min)
			window->map->z_min = go->z1;
		if (go->z0 > window->map->z_max)
			window->map->z_max = go->z0;
		if (go->z1 > window->map->z_max)
			window->map->z_max = go->z1;
		go = go->next;
	}
}

void	block_movement(t_window *window)
{
	if (window->block == 0)
		window->block = 1;
	else
		window->block = 0;
}
