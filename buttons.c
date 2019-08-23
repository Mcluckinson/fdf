/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:06:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/23 19:57:16 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
///////ЭТА ФУНКЦИЯ КЛАДЕТСЯ В КЕЙ ХУК, МЛХ САМ ОПРЕДЕЛЯЕТ, КАКАЯ КЛАВИША НАЖАТА И КЛАДЕТ В int key соответствующий код
int key_press(int key, t_window *window)
{
	if (key == 53)
		close_window(window);
	if (key == 18)
		draw_parallel(window);
	if (key == 19)
		draw_iso(window);
	if (key >= 123 && key <= 126)
		move(key, window);
	if (key == 69)
		zoom_in(window);
	if (key == 78)
		zoom_out(window);
	if (key == 29)
		randomise_colors(window);
	if (key == 13 || key == 1)
		change_altitude(key, window);
	if (key == 21)
		change_gradient(window);
	if (key == 23)
	{
		window->color[0] = 0xffff00;
		window->color[1] = 0xee82ee;
		gradient1(window);
	}
	if (key == 22)
	{
		window->color[0] = 0x008000;
		window->color[1] = 0xffa500;
		gradient2(window);
	}
	if (key == 26)
	{
		window->color[0] = 0xb0c4de;
		window->color[1] = 0xc71585;
		gradient3(window);
	}
	return (0);


}

int close_window(t_window *window)
{
	del_win(window);
	exit(0);
}
///////СБРАСЫВАЕТ ИЗМЕНЕНИЯ И РИСУЕТ ПАРАЛЛЕЛЬНУЮ ПРОЕКЦИЮ В ЦЕНТРЕ
void	draw_parallel(t_window *window)
{
	window->cur_zoom = 1;
	window->map->x_max = 0;
	window->map->x_min = 0;
	window->map->y_max = 0;
	window->map->y_min = 0;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	del_coords(window->turned);
	del_coords(window->current);
	window->turned = parallel(window->lines, window->map, window);
	window->current = parallel(window->lines, window->map, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}
////////СБРАСЫВАЕТ ИЗМЕНЕНИЯ, РИСУЕТ ИЗОМЕТРИЧЕСКУЮ ПРОЕКЦИЮ В ЦЕНТРЕ
void 	draw_iso(t_window *window)
{
	window->cur_zoom = 1;
	window->map->x_max = 0;
	window->map->x_min = 0;
	window->map->y_max = 0;
	window->map->y_min = 0;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	del_coords(window->turned);
	del_coords(window->current);
	window->current = iso(window->lines, window->map, window);
	window->turned = iso(window->lines, window->map, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}
////////ДВИЖЕНИЕ ПО СТРЕЛКАМ
void	move(int key, t_window *window)
{
	if (key == 124)
		move_right(window);
	if (key == 123)
		move_left(window);
	if (key == 126)
		move_up(window);
	if (key == 125)
		move_down(window);
}
////////МЫШЬ
int mouse_buttons(int key, int x, int y, t_window *window)
{
	//////DONT FORGET THIS X=Y SHIT
	x = y;//////////ТО ЖЕ САМОЕ ЧТО int key. MLX САМА ОПРЕДЕЛЯЕТ КООРДИНАТЫ КУРСОРА И КЛАДЕТ ИХ В Х и У
	if (key == 4)
		zoom_in(window);
	if (key == 5)
		zoom_out(window);
	return (0);
}
///////МЕНЯЕТ ТИП ГРАДЕНТА ПО КНОПКЕ 4 и ПЕРЕРИСОВЫВАЕТ КАРТУ
void	change_gradient(t_window *window)
{
	if (window->gradient_mod == 0)
		window->gradient_mod = 1;
	else
		window->gradient_mod = 0;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
