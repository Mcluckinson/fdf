/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:34:49 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/31 18:30:49 by cyuriko          ###   ########.fr       */
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
		if (go->y0 < 0 || go->y1 < 0)
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
		if (go->y0 > MAP_H - 300 || go->y1 > MAP_H - 300)
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

void	zoom_in(t_window *window)
{
	if (window->cur_zoom > 0.5)
		window->cur_zoom -= 0.1;
	else
		return ;
//	copy_to_current(window->turned, window);
	fix_current(window->turned, window, window->cur_zoom);
//	go = fix_orig(window->turned, 0.9);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	zoom_out(t_window *window)
{
	window->cur_zoom += 0.1;
//	copy_to_current(window->turned, window);
	fix_current(window->turned, window, window->cur_zoom);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	fix_current(t_coords *start, t_window *window, float ratio)
{
	t_coords *go;
	t_coords *result;

	go = start;
	result = window->current;
	while (go!= NULL)
	{
		result->x0 = go->x0 * ratio;
		result->x1 = go->x1 * ratio;
		result->y0 = go->y0 * ratio;
		result->y1 = go->y1 * ratio;
		result->z0 = go->z0 * ratio;
		result->z1 = go->z1 * ratio;
		result = result->next;
		go = go->next;
	}
}

t_coords	*init_current(t_window *window)
{
	t_coords	*result;
	t_coords	*go;

	go = window->turned;
	while (go != NULL)
	{
		result = new_coords_from_above(result);
		go = go->next;
	}
	return (result);
}

void	copy_to_current(t_coords *start, t_window *window)
{
	t_coords *go;
	t_coords *change;

	go = start;
	change = window->current;
	while (go != NULL)
	{
		change->x0 = go->x0;
		change->x1 = go->x1;
		change->y0 = go->y0;
		change->y1 = go->y1;
		change->z0 = go->z0;
		change->z1 = go->z1;
		go = go->next;
		change = change->next;
	}
}