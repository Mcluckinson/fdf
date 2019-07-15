/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:17:22 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/14 17:47:13 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*new_coords(t_coords *coords)
{
	t_coords	*new;

	new = (t_coords*)malloc(sizeof(t_coords));
	if (!coords)
		new->next = NULL;
	else
		new->next = coords;
	return (new);
}

t_coords	*get_lines(t_map *map)
{
	t_coords	*line;

	line = NULL;
	line = get_horisontal(line, map);
	line = get_vertical(line, map);
	fix_orig(line);
	return (line);
}

t_coords	*get_horisontal(t_coords *line, t_map *map)
{
//	t_coords	*new;
	int rows;
	int cols;

///	new = line;
	rows = 0;
	while (rows < map->y)
	{
		cols = 0;
		while (cols < map->x - 1)
		{
			line = new_coords(line);
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
	return (line);
}

t_coords		*get_vertical(t_coords *line, t_map *map)
{
//	t_coords	*new;
	int rows;
	int cols;

	cols = 0;
	while (cols < map->x)
	{
		rows = 0;
		while (rows < map->y - 1)
		{
			line = new_coords(line);
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