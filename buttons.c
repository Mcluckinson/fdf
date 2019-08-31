/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:06:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/31 18:19:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_press(int key, t_window *window)
{
	if (key == 53)
		close_window(window);
	if (window->map != NULL)
	{
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
		if (key == 23 || key == 22 || key == 26 || key == 28)
			gradient(window, key);
		if (key == 49)
			block_movement(window);
	}
	return (0);
}

int		close_window(t_window *window)
{
	del_win(window);
	exit(0);
}

void	draw_parallel(t_window *window)
{
	window->projection = 1;
	window->cur_zoom = 1;
	window->map->x_max = 0;
	window->map->x_min = 0;
	window->map->y_max = 0;
	window->map->y_min = 0;
	window->height_mod = 0;
	fix_altitude(window);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	del_coords(window->turned);
	del_coords(window->current);
	window->turned = parallel(window->lines, window);
	window->current = parallel(window->lines, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}

void	draw_iso(t_window *window)
{
	window->projection = 2;
	window->cur_zoom = 1;
	window->map->x_max = 0;
	window->map->x_min = 0;
	window->map->y_max = 0;
	window->map->y_min = 0;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	window->height_mod = 0;
	fix_altitude(window);
	del_coords(window->turned);
	del_coords(window->current);
	window->current = iso(window->lines, window);
	window->turned = iso(window->lines, window);
	move_position(window->current, window->map);
	draw_map(window->current, window);
	window->cur_x = 0;
	window->cur_y = 0;
}

int		mouse_buttons(int key, int x, int y, t_window *window)
{
	x = y;
	if (key == 4)
		zoom_in(window);
	if (key == 5)
		zoom_out(window);
	return (0);
}
