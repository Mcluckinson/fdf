/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:06:09 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/31 14:45:31 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_press(int key, t_window *window)
{
//	mlx_do_key_autorepeaton(window->mlx_ptr);
	if (key == 53)
		close_window(window);
	if (key == 18)
		draw_parallel(window);
	if (key == 19)
		draw_iso(window);
	if (key >= 123 && key <= 126)
	{
		if (key == 124)
			move_right(window);
		if (key == 123)
			move_left(window);
		if (key == 126)
		{
			move_up(window);
			window->current = init_current(window);
		}
		if (key == 125)
			move_down(window);
	}
	if (key == 69)
		zoom_in(window);
	if (key == 78)
		zoom_out(window);
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
	window->turned = parallel(window->lines, window->map);
	draw_map(window->turned, window);
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
	window->turned = iso(window->lines, window->map);
	draw_map(window->turned, window);
}