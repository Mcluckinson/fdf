/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:34:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/28 16:39:11 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	move_right(t_window *window)
{
	t_coords *go;

	if (window->map->x_max >= MAP_W)
		return ;
	go = window->turned;
	while (go != NULL)
	{
		go->x0++;
		go->x1++;
		find_max_min(go, window->map);
		go = go->next;
	}
	if (window->map->x_max >= MAP_W)
		return ;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->turned, window);
}

void 	move_left(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;
	go = window->turned;
	while (go != NULL)
	{
		go->x0--;
		go->x1--;
		if (go->x0 <= 0 || go->x1 <= 0)
			flag = 1;
		go = go->next;
	}
	if (flag == 1)
	{
		move_right(window);
		return;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->turned, window);
}

void 	move_up(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;

	go = window->turned;
	while (go != NULL)
	{
		go->y0--;
		go->y1--;
		if (go->y0 <= 0 || go->y1 <= 0)
			flag = 1;
		go = go->next;
	}
	if (flag == 1)
	{
		move_down(window);
		return;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->turned, window);
}

void 	move_down(t_window *window)
{
	t_coords *go;

	if (window->map->y_max >= MAP_H - 300)
		return ;
	go = window->turned;
	while (go != NULL)
	{
		go->y0++;
		go->y1++;
		find_max_min(go, window->map);
		go = go->next;
	}
	if (window->map->y_max >= MAP_W)
		return ;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->turned, window);
}
