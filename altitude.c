/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altitude.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 18:15:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/13 15:33:08 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/////УВЕЛИЧИТ ВЫСОТУ ПО НАЖАТИЮ W
void increase_upper(t_window *window)
{
	t_coords *go;

	window->height_mod = 10;////НА ЭТО ЗНАЧЕНИЕ МЕНЯЕТСЯ ВЫСОТА, ПО УМОЛЧАНИЮ 0
	go = window->lines;
	while (go != NULL)
	{
		if (go->z1orig != 0)////ПРОВЕРЯЕМ ЗНАЧЕНИЕ ОРИГИНАЛЬНОЙ ВЫСОТЫ
			go->z1 += window->height_mod;/////МЕНЯЕМ ЗНАЧЕНИЕ ФАКТИЧЕСКОЙ
		if (go->z0orig != 0)////ТО ЖЕ СО ВТОРОЙ ВЫСОТОЙ
			go->z0 += window->height_mod;
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300)); ////ЗАНУЛЯЕМ МАССИВ С ИНФОРМАЦИЕЙ О ПИКСЕЛЯХ
	redraw_altitude(window);////ПЕРЕСЧИТЫВАЕМ КООРДИНАТЫ С НОВЫМИ ВЫСОТАМИ
	fix_current(window->current, window->current, window->cur_zoom, window); ////ДОБАВЛЯЕМ ПРОЧИЕ ИЗМЕНЕНИЯ
	move_position(window->current, window->map); ///ДВИГАЕМ НА ПРЕЖНЕЕ МЕСТО
	draw_map(window->current, window);////РИСУЕМ
}
////ТО ЖЕ НО УМЕНЬШАЕТ ВЫСОТУ ПО НАЖАТИЮ S
void decrease_upper(t_window *window)
{
	t_coords *go;

	window->height_mod = -10;
	go = window->lines;
	while (go != NULL)
	{
		if (go->z1orig != 0)
			go->z1 += window->height_mod;
		if (go->z0orig != 0)
			go->z0 += window->height_mod;
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	redraw_altitude(window);
	fix_current(window->current, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
}
////СМЕШНАЯ ФУНКЦИЯ КОТОРАЯ КИДАЕТ СЛУЧАЙНЫЕ ЦВЕТА
void	randomise_colors(t_window *window)
{
	t_coords *go;

	go = window->current;
	while (go != NULL)
	{
		go->color_finish = rand();
		go->color_start = rand();
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
//////МЕНЯЕМ КООРДИНАТЫ Х и У для изометрии, т.к они зависят от высоты
void	redraw_altitude(t_window *window)
{
	t_coords	*orig;
	t_coords	*go;

	orig = window->lines;
	go = window->current;

	while (orig != NULL)
	{
		go->x0 = (orig->x0 - orig->y0)  * cos(0.523599);
		go->x1 = (orig->x1 - orig->y1)  * cos(0.523599);
		go->y0 = (orig->z0) * -1 + ((orig->x0 + orig->y0)  * sin(0.523599));
		go->y1 = (orig->z1) * -1 + ((orig->x1 + orig->y1)  * sin(0.523599));
		go->z0 = orig->z0;
		go->z1 = orig->z1;
		go->color_start = window->color[0]; ////КИАЮ ЦВЕТА НА ВСЯКИЙ СЛУЧАЙ, СТОИТ ПРОВЕРИТЬ, МОЖЕТ ЭТО ЛИШНЕЕ И ОНИ ТАМ БУДУТ ЛЕЖАТЬ И ТАК
		go->color_finish = window->color[1];
		orig = orig->next;
		go = go->next;
	}
}