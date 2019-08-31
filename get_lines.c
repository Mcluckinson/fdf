/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:17:22 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 14:11:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords		*new_coords(t_coords *coords)
{
	t_coords	*new;

	if (!(new = (t_coords*)malloc(sizeof(t_coords))))
		return (NULL);
	new->x0 = 0;
	new->x1 = 0;
	new->y0 = 0;
	new->y1 = 0;
	new->z0 = 0;
	new->z1 = 0;
	new->z0orig = 0;
	new->z1orig = 0;
	new->color_flag_finish = 0;
	new->color_flag_start = 0;
	if (coords != NULL)
		coords->next = new;
	new->next = NULL;
	return (new);
}

t_coords		*new_coords_from_above(t_coords *coords)
{
	t_coords	*new;

	if (!(new = (t_coords*)malloc(sizeof(t_coords))))
		return (NULL);
	new->x0 = 0;
	new->x1 = 0;
	new->y0 = 0;
	new->y1 = 0;
	new->z0 = 0;
	new->z1 = 0;
	new->z0orig = 0;
	new->z1orig = 0;
	new->color_flag_start = 0;
	new->color_flag_finish = 0;
	if (coords != NULL)
		new->next = coords;
	else
		new->next = NULL;
	return (new);
}

t_coords		*get_lines(t_map *map)
{
	t_extra		*setka;
	t_coords	*line;
	t_coords	*start;

	if (!(setka = (t_extra*)malloc(sizeof(t_extra))))
		return (NULL);
	line = NULL;
	if (map->x > 1)
		line = get_horisontal(line, map, setka);
	start = line;
	if (map->y > 1)
	{
		if (!(line = get_vertical(line, map, setka)))
			del_coords(start);
	}
	if (line)
		line = fix_orig(line, 20);
	free(setka);
	return (line);
}

t_coords		*get_horisontal(t_coords *line, t_map *map, t_extra *setka)
{
	t_coords	*result;

	setka->rows_actual = map->y * -1 / 2;
	result = NULL;
	setka->rows = 0;
	while (setka->rows < map->y)
	{
		setka->cols = 0;
		setka->cols_actual = map->x * -1 / 2;
		while (setka->cols < map->x - 1)
		{
			if (!(line = new_coords(line)))
			{
				if (result)
					del_coords(result);
				return (NULL);
			}
			if (setka->cols == 0 && setka->rows == 0)
				result = line;
			add_horosontal(setka, line, map);
		}
		setka->rows++;
		setka->rows_actual++;
	}
	return (result);
}

t_coords		*get_vertical(t_coords *line, t_map *map, t_extra *setka)
{
	t_coords	*prev;

	setka->cols_actual = map->x * -1 / 2;
	setka->cols = 0;
	while (setka->cols < map->x)
	{
		setka->rows = 0;
		setka->rows_actual = map->y * -1 / 2;
		while (setka->rows < map->y - 1)
		{
			if (line)
				prev = line;
			if (!(line = new_coords_from_above(line)))
			{
				if (prev)
					del_coords(prev);
				return (NULL);
			}
			add_vertical(setka, line, map);
		}
		setka->cols++;
		setka->cols_actual++;
	}
	return (line);
}
