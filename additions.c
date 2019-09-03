/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:36:48 by samymone          #+#    #+#             */
/*   Updated: 2019/08/31 19:36:50 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_horosontal(t_extra *setka, t_coords *line, t_map *map)
{
	line->x0 = setka->cols_actual;
	line->x1 = setka->cols_actual + 1;
	line->z0 = map->z[setka->rows][setka->cols];
	line->z1 = map->z[setka->rows][setka->cols + 1];
	if (map->color[setka->rows][setka->cols])
	{
		line->color_start = map->color[setka->rows][setka->cols];
		line->color_flag_start = 1;
	}
	if (map->color[setka->rows][setka->cols + 1])
	{
		line->color_finish = map->color[setka->rows][setka->cols + 1];
		line->color_flag_finish = 1;
	}
	line->y0 = setka->rows_actual;
	line->y1 = setka->rows_actual;
	line->z0orig = line->z0;
	line->z1orig = line->z1;
	setka->cols++;
	setka->cols_actual++;
}

void		add_vertical(t_extra *setka, t_coords *line, t_map *map)
{
	line->y0 = setka->rows_actual;
	line->y1 = setka->rows_actual + 1;
	line->x0 = setka->cols_actual;
	line->x1 = setka->cols_actual;
	line->z0 = map->z[setka->rows][setka->cols];
	line->z0orig = line->z0;
	line->z1 = map->z[setka->rows + 1][setka->cols];
	line->z1orig = line->z1;
	if (map->color[setka->rows][setka->cols])
	{
		line->color_start = map->color[setka->rows][setka->cols];
		line->color_flag_start = 1;
	}
	if (map->color[setka->rows + 1][setka->cols])
	{
		line->color_finish = map->color[setka->rows + 1][setka->cols];
		line->color_flag_finish = 1;
	}
	setka->rows++;
	setka->rows_actual++;
}

void		del_coords(t_coords *lines)
{
	if (lines != NULL)
		del_coords(lines->next);
	free(lines);
}
