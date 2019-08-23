/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 15:31:50 by samymone          #+#    #+#             */
/*   Updated: 2019/08/23 15:31:52 by samymone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	gradient1(t_window *window)
{
	t_coords *go;

	go = window->current;
	while (go != NULL)
	{
		go->color_finish = 0xffff00;
		go->color_start = 0xee82ee;
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	gradient2(t_window *window)
{
	t_coords *go;

	go = window->current;
	while (go != NULL)
	{
		go->color_finish = 0x008000;
		go->color_start = 0xffa500;
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	gradient3(t_window *window)
{
	t_coords *go;

	go = window->current;
	while (go != NULL)
	{
		go->color_finish = 0xb0c4de;
		go->color_start = 0xc71585;
		go = go->next;
	}
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
