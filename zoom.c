/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:41:27 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 18:04:43 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in(t_window *window)
{
	window->cur_zoom += 0.1;
	if (window->projection == 2)
	{
		fix_altitude(window);
		redraw_altitude(window->current, window);
		redraw_altitude(window->turned, window);
	}
	window->turned = fix_orig(window->turned, window->fix_ratio);
	window->current = fix_orig(window->current, window->fix_ratio);
	fix(window->turned, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}

void	zoom_out(t_window *window)
{
	if (window->cur_zoom > 0.5)
		window->cur_zoom -= 0.1;
	else
		return ;
	if (window->projection == 2)
	{
		fix_altitude(window);
		redraw_altitude(window->current, window);
		redraw_altitude(window->turned, window);
	}
	window->turned = fix_orig(window->turned, window->fix_ratio);
	window->current = fix_orig(window->current, window->fix_ratio);
	fix(window->turned, window->current, window->cur_zoom, window);
	move_position(window->current, window->map);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	draw_map(window->current, window);
}
