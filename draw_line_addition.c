/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_addition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:10:10 by samymone          #+#    #+#             */
/*   Updated: 2019/09/03 13:09:09 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line(t_coords *line, t_window *window)
{
	int				coord[4];
	int				incr[4];
	int				ixy[3];
	unsigned int	final_color;
	int				*steep;

	pre_draw_line(coord, line);
	steep = steep_check(&coord[0], &coord[1], &coord[2], &coord[3]);
	inter_via_mass(coord, incr);
	ixy[2] = coord[2];
	ixy[1] = coord[0];
	while (ixy[1]++ <= coord[1])
	{
		final_color = get_color(ixy[1], line, steep);
		if (!check_shit(ixy, steep))
		{
			ixy[0] = find_i(ixy[1], ixy[2], window, steep);
			put_color(window->img_data, ixy[0], final_color);
		}
		finish_count(ixy, incr);
	}
	free(steep);
}

int			find_i(int x, int y, t_window *window, int *steep)
{
	int				i;

	if (steep[0] == 0)
		i = (x * (*window->depth / 8)) + (y * (*window->linesize));
	else
		i = (y * (*window->depth / 8)) + (x * (*window->linesize));
	return (i);
}

void		recol_map(t_coords *go, t_window *window, t_coords *start)
{
	while (go != NULL)
	{
		gr1(go, window, start);
		go = go->next;
		start = start->next;
	}
}
