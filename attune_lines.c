/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attune_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:14:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/20 14:56:52 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*fix_orig(t_coords *start, float ratio)
{
	t_coords	*result;

	result = start;
	while (start!= NULL)
	{
		start->x0 = start->x0 * ratio;
		start->x1 = start->x1 * ratio;
		start->y0 = start->y0 * ratio;
		start->y1 = start->y1 * ratio;
		start->z0 = start->z0 * ratio;
		start->z1 = start->z1 * ratio;
		start = start->next;
	}
	return (result);
}

t_coords	*iso(t_coords *start, t_map *map)
{
	t_coords *turned;
	t_coords	*result;

	turned = NULL;
	result = turned;
	while (start != NULL)
	{
		if (!(turned = new_coords(turned)))
		{
			if (result != NULL)
				del_coords(result);
			return (NULL);
		}
		if (result == NULL)
			result = turned;
		turned->x0 = (start->x0 - start->y0)  * cos(0.523599);
		turned->x1 = (start->x1 - start->y1)  * cos(0.523599);
		turned->y0 = (start->z0) * -1 + ((start->x0 + start->y0)  * sin(0.523599));
		turned->y1 = (start->z1) * -1 + ((start->x1 + start->y1)  * sin(0.523599));
		turned->z0 = start->z0;
		turned->z1 = start->z1;
		find_max_min(turned, map);
		start = start->next;
	}
	result = resize_all(result, map);
	result = move_position(result, map);
	return (result);
}

void	find_max_min(t_coords *turned, t_map *map)
{
	if (turned->x0 > map->x_max)
		map->x_max = turned->x0;
	if (turned->x1 > map->x_max)
		map->x_max = turned->x1;
	if (turned->y0 > map->y_max)
		map->x_max = turned->x0;
	if (turned->y1 > map->y_max)
		map->y_max = turned->y1;
	if (turned->x0 < map->x_min && turned->x0 < 0)
		map->x_min = turned->x0;
	if (turned->x1 < map->x_min && turned->x1 < 0)
		map->x_min = turned->x1;
	if (turned->y0 < map->y_min && turned->y0 < 0)
		map->x_min = turned->x0;
	if (turned->y1 < map->y_min && turned->y1 < 0)
		map->y_min = turned->y1;
}

t_coords	*move_position(t_coords *start, t_map *map)
{
	t_coords	*result;
	result = start;
	while (start != NULL)
	{
		start->x0 = (start->x0 - map->x_min);
		start->x1 = (start->x1 - map->x_min);
		start->y0 = (start->y0 - map->y_min);
		start->y1 = (start->y1 - map->y_min);
		start = start->next;
	}
	return (result);
}

t_coords	*resize_all(t_coords *start, t_map *map)
{
	float 		ratio;
	float 		ratiox;
	float 		ratioy;

	ratiox = 1;
	ratioy = 1;
	if (map->x_max - map->x_min + 1 > 2000)
		ratiox = 2000 / (float)(map->x_max - map->x_min);
	if (map->y_max - map->y_min + 1 > 1000)
		ratioy = 1000 / (float)(map->y_max - map->y_min);
	ratio = fminf(ratiox, ratioy);
	if (ratio != 1)
	{
		start = fix_orig(start, ratio);
		map->y_max *= ratio;
		map->y_min *= ratio;
		map->x_max *= ratio;
		map->x_min *= ratio;
	}
	return (start);
}