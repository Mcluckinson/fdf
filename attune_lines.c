/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attune_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:14:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/24 22:33:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/////////////ПРОСТО ПЕРЕМНОЖАЕТ ЗНАЧЕНИЯ НА ratio
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
		start->z0orig *= ratio;
		start->z1orig *= ratio;
		start = start->next;
	}
	return (result);
}
/////ПРЕВРАЩАЕТ ОРИГИНАЛЬНЫЕ КООРДИНАТЫ В КООРДИНАТЫ ДЛЯ ИЗОМЕТРИЧЕСКОЙ ПРОЕКЦИИ, СОЗДАВАЯ НОВуЮ СТРУКТУРУ С ЭТИМИ ДАННЫМИ
t_coords	*iso(t_coords *start, t_map *map, t_window *window)
{
	t_coords	*turned;
	t_coords	*result;

	map->x_min = 0;
	map->x_max = 0;
	map->y_max = 0;
	map->y_min = 0;
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
		turned->x0 = (start->x0 - start->y0)  * cos(0.523599);//////////В КУКБУКЕ ЕСТЬ ПРО ЭТО СТАТЬЯ
		turned->x1 = (start->x1 - start->y1)  * cos(0.523599);
		turned->y0 = (start->z0) * -1 + ((start->x0 + start->y0)  * sin(0.523599));
		turned->y1 = (start->z1) * -1 + ((start->x1 + start->y1)  * sin(0.523599));
		turned->z0 = start->z0;
		turned->z1 = start->z1;
		turned->color_start = window->color[0];//////////КЛАДУ ЦВЕТА ЧТОБЫ ПОТОМ СЧИТАТЬ ГРАДИЕНТ
		turned->color_finish = window->color[1];
		find_max_min(turned, map);//////////СЕРВИСНАЯ ФУНКЦИЯ, ЧТОБЫ ПОТОМ МЕНЯТЬ РАЗМЕР
		start = start->next;
	}
	result = resize_all(result, map);///////СОБСТВЕННО МЕНЯЮ РАЗМЕР ЕСЛИ КАРТА СЛИШКОМ БОЛЬШАЯ (НАПРИМЕР МАРС)
	return (result);
}
////////////////ДЕЛАЕТ НОВЫЙ КООРДИНАТЫ С ПАРАЛЛЕЛЛЬНОЙ ПРОЕКЦИЕЙ ПО АНАЛОГИИ С ПРЕДЫДУЩЕЙ ФУНКЦИЕЙ
t_coords	*parallel(t_coords *start, t_map *map, t_window *window)
{
	t_coords	*fixed;
	t_coords	*result;

	fixed = NULL;
	result = fixed;
	map->x_min = 0;
	map->x_max = 0;
	map->y_max = 0;
	map->y_min = 0;
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
		fixed->color_start = window->color[0];
		fixed->color_finish = window->color[1];
		find_max_min(fixed, map);
		start = start->next;
	}
	result = resize_all(result, map);
	return (result);
}
/////////ЗАПИСЫВАЕТ В  t_map *map макс мин значения
void	find_max_min(t_coords *turned, t_map *map)
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
////////////ДВИГАЕТ КАРТУ В ЦЕНТР, СОХРАНЯЯ ПЕРЕДВИЖЕНИЕ ПО СТРЕЛКАМ, ЕСЛИ ОНО БЫЛО
t_coords	*move_position(t_coords *start, t_map *map)
{
	t_coords	*result;
	result = start;
	int width_mod;
	int height_mod;

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
///////////////////МЕНЯЕТ РАЗМЕР КАРТЫ ПРИ НЕОБХОДИМОСТИ
t_coords	*resize_all(t_coords *start, t_map *map)
{
	float 		ratio;
	float 		ratiox;
	float 		ratioy;

	ratiox = 1;
	ratioy = 1;
	if (map->x_max - map->x_min > 2000)
		ratiox = MAP_W / (float)(map->x_max - map->x_min);
	if (map->y_max - map->y_min > 1000)
		ratioy = (MAP_H - 300) / (float)(map->y_max - map->y_min);
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