/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 20:47:24 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/29 21:43:46 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*init_current(t_window *window)
{
	t_coords	*result;
	t_coords	*go;

	go = window->turned;
	result = window->current;
	while (go != NULL)
	{
		result = new_coords_from_above(result);
		go = go->next;
	}
	return (result);
}

void		copy_to_current(t_coords *origin, t_coords *target)
{
	t_coords *go;
	t_coords *change;

	go = origin;
	change = target;
	while (go != NULL)
	{
		change->x0 = go->x0;
		change->x1 = go->x1;
		change->y0 = go->y0;
		change->y1 = go->y1;
		change->z0 = go->z0;
		change->z1 = go->z1;
		change->color_start = go->color_start;
		change->color_finish = go->color_finish;
		go = go->next;
		change = change->next;
	}
}

void		fix_current(t_coords *s1, t_coords *s2, float r, t_window *window)
{
	if (s1 != NULL)
	{
		fix_current(s1->next, s2->next, r, window);
		s2->x0 = (s1->x0 * r + (5 * window->cur_x));
		s2->x1 = (s1->x1 * r + (5 * window->cur_x));
		s2->y0 = (s1->y0 * r + (5 * window->cur_y));
		s2->y1 = (s1->y1 * r + (5 * window->cur_y));
		s2->z0 = s1->z0 * r;
		s2->z1 = s1->z1 * r;
	}
	return ;
}

void		find_max_min(t_coords *turned, t_map *map)
{
	if (turned->x0 > map->x_max)
		map->x_max = turned->x0;
	if (turned->x1 > map->x_max)
		map->x_max = turned->x1;
	if (turned->y0 > map->y_max)
		map->y_max = turned->y0;
	if (turned->y1 > map->y_max)
		map->y_max = turned->y1;
	if (turned->x0 < map->x_min && turned->x0 < 0)
		map->x_min = turned->x0;
	if (turned->x1 < map->x_min && turned->x1 < 0)
		map->x_min = turned->x1;
	if (turned->y0 < map->y_min && turned->y0 < 0)
		map->y_min = turned->y0;
	if (turned->y1 < map->y_min && turned->y1 < 0)
		map->y_min = turned->y1;
}
