/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 15:31:50 by samymone          #+#    #+#             */
/*   Updated: 2019/08/30 14:11:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_gradient(t_window *window)
{
	if (window->gradient_mod == 0)
		window->gradient_mod = 1;
	else
		window->gradient_mod = 0;
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	gradient(t_window *window, int key)
{
	t_coords *go;

	go = window->current;
	gradiend_distr(key, window);
	while (go != NULL)
	{
		go->color_finish = window->color[0];
		go->color_start = window->color[1];
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	gradiend_distr(int key, t_window *window)
{
	if (key == 23)
	{
		window->color[0] = 0xffff00;
		window->color[1] = 0xee82ee;
	}
	if (key == 22)
	{
		window->color[0] = 0x008000;
		window->color[1] = 0xffa500;
	}
	if (key == 26)
	{
		window->color[0] = 0xb0c4de;
		window->color[1] = 0xc71585;
	}
}

void	randomise_colors(t_window *window)
{
	t_coords *go;

	window->gradient_mod = 3;
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
