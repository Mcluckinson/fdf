/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:34:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/28 18:25:42 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	move_right(t_window *window)
{
	t_coords *go;
	int 	flag;

	flag = 0;
	go = window->turned;
	while (go != NULL)
	{
		go->x0+=5;
		go->x1+=5;
		if (go->x0 >= MAP_W || go->x1 >= MAP_W)
			flag = 1;
		go = go->next;
	}
	if (flag == 1)
	{
		move_left(window);
		return ;
	}
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
		go->x0-=5;
		go->x1-=5;
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
		go->y0-=5;
		go->y1-=5;
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
	int 	flag;

	flag = 0;
	go = window->turned;
	while (go != NULL)
	{
		go->y0+=5;
		go->y1+=5;
		if (go->y0 >= MAP_H - 300 || go->y1 >= MAP_H - 300)
			flag = 1;
		go = go->next;
	}
	if (flag == 1)
	{
		move_up(window);
		return;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->turned, window);
}
