/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 15:19:07 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				draw_map(t_coords *lines, t_window *window)
{
	t_coords	*go;

	go = lines;
	if (window->gradient_mod == 1)
		find_max_min_z(go, window);
	recolor_map(go, window);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	while (go != NULL)
	{
		draw_line(go, window);
		go = go->next;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr,
			window->img_ptr, 0, 0);
	return (0);
}

void			recolor_map(t_coords *lines, t_window *window)
{
	t_coords *go;
	t_coords *start;

	start = window->lines;
	go = lines;
	if (window->gradient_mod == 1)
	{
		while (go != NULL)
		{
			gr2(go, window, start);
			go = go->next;
			start = start->next;
		}
	}
	else
	{
		while (go != NULL)
		{
			gr1(go, window, start);
			go = go->next;
			start = start->next;
		}
	}
}

void			gr2(t_coords *line, t_window *window, t_coords *start)
{
	if (!start->color_flag_start)
		line->color_start = color_for_z(line->z0, window);
	else
		line->color_start = start->color_start;
	if (!start->color_flag_finish)
		line->color_finish = color_for_z(line->z1, window);
	else
		line->color_finish = start->color_finish;
}

void			gr1(t_coords *line, t_window *window, t_coords *start)
{
	if (!start->color_flag_start)
		line->color_start = window->color[0];
	else
		line->color_start = start->color_start;
	if (!start->color_flag_finish)
		line->color_finish = window->color[1];
	else
		line->color_finish = start->color_finish;
}

unsigned int	color_for_z(int z, t_window *window)
{
	double			percentage;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	percentage = percent(window->map->z_min, window->map->z_max, z);
	red = light((window->color[0] >> 16) & 0xFF,
			(window->color[1] >> 16) & 0xFF, percentage);
	green = light((window->color[0] >> 8) & 0xFF,
			(window->color[1] >> 8) & 0xFF, percentage);
	blue = light(window->color[0] & 0xFF,
			window->color[1] & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
