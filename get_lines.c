/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:17:22 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/28 23:40:15 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
////СОЗДАЕТ НОВЫЙ ЭЛЕМЕНТ t_coords
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
	new->z0orig = 0;
	new->z1orig = 0;
	new->color_flag_finish = 0;
	new->color_flag_start = 0;
	if (coords != NULL)
		coords->next = new;
	new->next = NULL;
	return (new);
}
////НОВЫЙ ЭЛЕМЕНТ t_coords цепляющийся с другой стороны. Хуево и костыльно
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
/////СОБИРАЕТ ПОЛОСКИ t_coords из данных в t_map *map.
t_coords	*get_lines(t_map *map)
{
	t_coords	*line;
	t_coords	*start;

	line = NULL;
	line = get_horisontal(line, map);///СНАЧАЛА ГОРИЗОНТАЛЬНЫЕ
	start = line;
	if (!(line = get_vertical(line, map)))/////ПОТОМ ВЕРТИКАЛЬНЫЕ
		del_coords(start);
	if (line)
		line = fix_orig(line, 20);////УМНОЖАЕТ ВСЕ НА 20 (Я ПРОСТО ВЫБРАЛ ТАКОЕ ЗНАЧЕНИЕ ПО УМОЛЧАНИЮ, ИНАЧЕ ДЛИНЫ ПОЛОСОК БУДУТ РАВНЫ 1
	return (line);
}

t_coords	*get_horisontal(t_coords *line, t_map *map)
{
	int			rows;////СЧЕТЧИК ПО У
	int			cols;////СЧЕТЧИК ПО Х
	//////ПРОБУЮ ЭТИ ДВЕ ПЕРЕМЕННЫЕ ВНИЗУ КЛАСТЬ В КООРДИНАТЫ
	int 		rows_actual;
	int 		cols_actual;
	t_coords	*result;

	rows_actual = map->y * -1 / 2;

	result = NULL;
	rows = 0;
	while (rows < map->y)
	{
		cols = 0;
		cols_actual = map->x * -1 / 2;
		while (cols < map->x - 1) //// НЕ ЗАГЛЯНЕТ В ПОСЛЕДНИЙ ЭЛЕМЕНТ СТРОКИ ПОТОМУ ЧТО ДАЛЬШЕ В ЦИКЛЕ ОН СМОТРИТ НА ТЕКУЩИЙ И НА СЛЕДУЮЩИЙ
		{
			if (!(line = new_coords(line)))
			{
				if (result)
					del_coords(result);
				return (NULL);
			}
			if (cols == 0 && rows == 0)
				result = line;
			line->x0 = cols_actual;
			line->x1 = cols_actual + 1;
			line->z0 = map->z[rows][cols];
			line->z1 = map->z[rows][cols + 1];
			if (map->color[rows][cols])
			{
				line->color_start = map->color[rows][cols];
				line->color_flag_start = 1;
			}
			if (map->color[rows][cols + 1])
			{
				line->color_finish = map->color[rows][cols + 1];
				line->color_flag_finish = 1;
			}
			line->y0 = rows_actual;
			line->y1 = rows_actual;
			line->z0orig = line->z0;/////ОРИГИНАЛЬНЫЕ ВЫСОТЫ ПОНАДОБЯТСЯ ДЛЯ ИЗМЕНЕНИЯ ВЫСОТЫ ПО КНОПКАМ
			line->z1orig = line->z1;
			cols++;
			cols_actual++;
		}
		rows++;
		rows_actual++;
	}
	return (result);
}

t_coords		*get_vertical(t_coords *line, t_map *map)
{
	int rows;
	int cols;
	//////ПРОБУЮ ЭТИ ДВЕ ПЕРЕМЕННЫЕ ВНИЗУ КЛАСТЬ В КООРДИНАТЫ
	int 		rows_actual;
	int 		cols_actual;
	t_coords *prev;


	cols_actual = map->x * -1 / 2;
	cols = 0;
	while (cols < map->x)
	{
		rows = 0;
		rows_actual = map->y * -1 / 2;
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
			line->y0 = rows_actual;
			line->y1 = rows_actual + 1;
			line->x0 = cols_actual;
			line->x1 = cols_actual;
			line->z0 = map->z[rows][cols];
			line->z0orig = line->z0;
			line->z1 = map->z[rows + 1][cols];
			line->z1orig = line->z1;
			if (map->color[rows][cols])
			{
				line->color_start = map->color[rows][cols];
				line->color_flag_start = 1;
			}
			if (map->color[rows + 1][cols])
			{
				line->color_finish = map->color[rows + 1][cols];
				line->color_flag_finish = 1;
			}
			rows++;
			rows_actual++;
		}
		cols++;
		cols_actual++;
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
}
