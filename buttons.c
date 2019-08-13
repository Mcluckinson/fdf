/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:06:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/12 19:00:10 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (key == 13)
		increase_upper(window);
	return (0);
}

int close_window(t_window *window)
{
	del_win(window);
	exit(0);
}

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
	window->turned = parallel(window->lines, window->map);
	window->current = parallel(window->lines, window->map);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}

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
	window->current = iso(window->lines, window->map);
	window->turned = iso(window->lines, window->map);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}

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

int mouse_buttons(int key, int x, int y, t_window *window)
{
	//////DONT FORGET THIS X=Y SHIT
	x = y;
	if (key == 4)
		zoom_in(window);
	if (key == 5)
		zoom_out(window);
	return (0);
}