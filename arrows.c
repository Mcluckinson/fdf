/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:34:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/24 12:06:38 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
//////////ПРОСТО МЕНЯЕТ КООРДИНАТЫ ПРИ НАЖАТИИ СТРЕЛКИ
void 	move_right(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;/////////////ЭТОТ ФЛАГ ОПРЕДЕЛЯЕТ, ВЫЛЕЗЛО ЛИ ИЗОБРАЖЕНИЕ ЗА ПРЕДЕЛЫ ЭКРАНА
	window->cur_x++;
	go = window->current;
	while (go != NULL)
	{
		go->x0+=5;
		go->x1+=5;
		if (go->x0 >= MAP_W || go->x1 >= MAP_W)
			flag = 1;
		go = go->next;
	}
	////////ДАЛЕЕ В КОММЕНТАХ ШТУКА, КОТОРАЯ ОТКАТЫВАЕТ ИЗМЕНЕНИЯ, ЕСЛИ ИЗОБРАЖЕНИЕ ВЫЛЕЗЛО ЗА ПРЕДЕЛЫ ЭКРАНА. ПОКА ЧТО УБРАНО ПОТОМУ ЧТО ПРИ ЗУМЕ ИНОГДА СЕГАЕТСЯ ИЛИ УХОДИТ В БЕСКОНЕЧНЫЙ ЦИКЛ
/*	if (flag == 1)
	{
		move_left(window);
		return ;
	}*/
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void 	move_left(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;
	window->cur_x--;
	go = window->current;
	while (go != NULL)
	{
		go->x0-=5;
		go->x1-=5;
		if (go->x0 <= 0 || go->x1 <= 0)
			flag = 1;
		go = go->next;
	}
/*	if (flag == 1)
	{
		move_right(window);
		return;
	}*/
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void 	move_up(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;
	go = window->current;
	window->cur_y--;
	while (go != NULL)
	{
		go->y0-=5;
		go->y1-=5;
		if (go->y0 < 0 || go->y1 < 0)
			flag = 1;
		go = go->next;
	}
/*	if (flag == 1)
	{
		move_down(window);
		return;
	}*/
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void 	move_down(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;
	go = window->current;
	window->cur_y++;
	while (go != NULL)
	{
		go->y0+=5;
		go->y1+=5;
		if (go->y0 > MAP_H - 300 || go->y1 > MAP_H - 300)
			flag = 1;
		go = go->next;
	}
/*	if (flag == 1)
	{
		move_up(window);
		return;
	}*/
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
////////ЭТО СОБСТВЕННО ЗУМ
void	zoom_in(t_window *window)
{
	window->cur_zoom += 0.1;
	fix_current(window->turned, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	zoom_out(t_window *window)
{
	if (window->cur_zoom > 0.5)
		window->cur_zoom -= 0.1;
	else
		return ;
	fix_current(window->turned, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
/////////////ВОТ ПОСЛЕ ПЕРЕДЕЛКИ КООРДИНАТ ВСЕ ДОЛЖНО КЛЕВО РАБОТАТЬ, А СЕЙЧАС ЗУМ ОТНОСИТЕЛЬНО ВЕРХНЕГО ЛЕВОГО УГЛА
void	fix_current(t_coords *start, t_coords *target, float ratio, t_window *window)
{
	if (start != NULL)
	{
		fix_current(start->next, target->next, ratio, window);
		target->x0 = (start->x0 * ratio + (5 * window->cur_x)) ;
		target->x1 = (start->x1 * ratio + (5 * window->cur_x));
		target->y0 = (start->y0 * ratio + (5 * window->cur_y));
		target->y1 = (start->y1 * ratio + (5 * window->cur_y));
		target->z0 = start->z0 * ratio;
		target->z1 = start->z1 * ratio;
	}
	return ;
}
////////////СОЗДАЕТ ПУСТОЙ t_coords *current
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
////////////КОПИРУЕТ В НЕГО ДАННЫЕ ИЗ ВЫБРАННОГО t_coords
void	copy_to_current(t_coords *origin, t_coords *target)
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
