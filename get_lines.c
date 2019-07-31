/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:17:22 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/31 13:36:59 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*new_coords(t_coords *coords)
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
	if (coords != NULL)
		coords->next = new;
	new->next = NULL;
	return (new);
}

t_coords	*new_coords_from_above(t_coords *coords)
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
	if (coords != NULL)
		new->next = coords;
	else
		new->next = NULL;
	return (new);
}

t_coords	*get_lines(t_map *map)
{
	t_coords	*line;
	t_coords	*start;

	line = NULL;
	line = get_horisontal(line, map);
	start = line;
	if (!(line = get_vertical(line, map)))
		del_coords(start);
	if (line)
		line = fix_orig(line, 20);
	return (line);
}

t_coords	*get_horisontal(t_coords *line, t_map *map)
{
	int rows;
	int cols;
	t_coords	*result;

	result = NULL;
	rows = 0;
	while (rows < map->y)
	{
		cols = 0;
		while (cols < map->x - 1)
		{
			if (!(line = new_coords(line)))
			{
				if (result)
					del_coords(result);
				return (NULL);
			}
			if (cols == 0 && rows == 0)
				result = line;
			line->x0 = cols;
			line->x1 = cols + 1;
			line->z0 = map->z[rows][cols];
			line->z1 = map->z[rows][cols + 1];
			line->y0 = rows;
			line->y1 = rows;
			cols++;
		}
		rows++;
	}
	return (result);
}

t_coords		*get_vertical(t_coords *line, t_map *map)
{
	int rows;
	int cols;
	t_coords *prev;

	cols = 0;
	while (cols < map->x)
	{
		rows = 0;
		while (rows < map->y - 1)
		{
			if (line)
				prev = line;
			if (!(line = new_coords_from_above(line)))
			{
				if (prev)
					del_coords(prev);
				return (NULL);
			}
			line->y0 = rows;
			line->y1 = rows + 1;
			line->x0 = cols;
			line->x1 = cols;
			line->z0 = map->z[rows][cols];
			line->z1 = map->z[rows + 1][cols];
			rows++;
		}
		cols++;
	}
	return (line);
}

void	del_coords(t_coords *lines)
{
	while (lines->next != NULL)
	{
		del_coords(lines->next);
		lines->next = NULL;
	}
	free(lines);
	lines = NULL;
}