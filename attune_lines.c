/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attune_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:14:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 14:11:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*fix_orig(t_coords *start, float ratio)
{
	t_coords	*result;

	result = start;
	while (start != NULL)
	{
		start->x0 = start->x0 * ratio;
		start->x1 = start->x1 * ratio;
		start->y0 = start->y0 * ratio;
		start->y1 = start->y1 * ratio;
		start->z0 = start->z0 * ratio;
		start->z1 = start->z1 * ratio;
		start->z0orig *= ratio;
		start->z1orig *= ratio;
		start = start->next;
	}
	return (result);
}

t_coords	*iso(t_coords *start, t_window *window)
{
	t_coords	*turned;
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
		turned->x0 = (start->x0 - start->y0) * cos(0.523599);
		turned->x1 = (start->x1 - start->y1) * cos(0.523599);
		turned->y0 = start->z0 * -1 + ((start->x0 + start->y0) * sin(0.523599));
		turned->y1 = start->z1 * -1 + ((start->x1 + start->y1) * sin(0.523599));
		turned->z0 = start->z0;
		turned->z1 = start->z1;
		find_max_min(turned, window->map);
		start = start->next;
	}
	result = resize_all(result, window);
	return (result);
}

t_coords	*parallel(t_coords *start, t_window *window)
{
	t_coords	*fixed;
	t_coords	*result;

	fixed = NULL;
	result = fixed;
	while (start != NULL)
	{
		if (!(fixed = new_coords(fixed)))
		{
			if (result != NULL)
				del_coords(result);
			return (NULL);
		}
		if (result == NULL)
			result = fixed;
		fixed->x0 = start->x0;
		fixed->x1 = start->x1;
		fixed->y0 = start->y0;
		fixed->y1 = start->y1;
		fixed->z0 = start->z0;
		fixed->z1 = start->z1;
		find_max_min(fixed, window->map);
		start = start->next;
	}
	result = resize_all(result, window);
	return (result);
}

t_coords	*move_position(t_coords *start, t_map *map)
{
	t_coords	*result;
	int			width_mod;
	int			height_mod;

	result = start;
	width_mod = (MAP_W - (map->x_max - map->x_min)) / 2;
	height_mod = (MAP_H - 300 - (map->y_max - map->y_min)) / 2;
	while (start != NULL)
	{
		start->x0 = (start->x0 - map->x_min + width_mod + 1);
		start->x1 = (start->x1 - map->x_min + width_mod + 1);
		start->y0 = (start->y0 - map->y_min + height_mod + 1);
		start->y1 = (start->y1 - map->y_min + height_mod + 1);
		start = start->next;
	}
	return (result);
}

t_coords	*resize_all(t_coords *start, t_window *window)
{
	float	ratio;
	float	ratiox;
	float	ratioy;

	ratiox = 1;
	ratioy = 1;
	if (window->map->x_max - window->map->x_min > 2000)
		ratiox = MAP_W / (float)(window->map->x_max - window->map->x_min);
	if (window->map->y_max - window->map->y_min > 1000)
		ratioy = (MAP_H - 300) / (float)(window->map->y_max - window->map->y_min);
	ratio = fminf(ratiox, ratioy);
	if (ratio != 1)
	{
		start = fix_orig(start, ratio);
		window->map->y_max *= ratio;
		window->map->y_min *= ratio;
		window->map->x_max *= ratio;
		window->map->x_min *= ratio;
		window->fix_ratio = ratio;
	}
	return (start);
}
