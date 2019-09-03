/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows_service.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:14:08 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/03 13:09:09 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_right(t_coords *lines)
{
	t_coords *go;

	go = lines;
	while (go != NULL)
	{
		if ((go->x0 + 5) >= MAP_W || (go->x1 + 5) >= MAP_W)
			return (1);
		go = go->next;
	}
	return (0);
}

static int	check_left(t_coords *lines)
{
	t_coords *go;

	go = lines;
	while (go != NULL)
	{
		if ((go->x0 - 5) <= 0 || (go->x1 - 5) <= 0)
			return (1);
		go = go->next;
	}
	return (0);
}

static int	check_up(t_coords *lines)
{
	t_coords *go;

	go = lines;
	while (go != NULL)
	{
		if ((go->y0 - 5) < 0 || (go->y1 - 5) < 0)
			return (1);
		go = go->next;
	}
	return (0);
}

static int	check_down(t_coords *lines)
{
	t_coords *go;

	go = lines;
	while (go != NULL)
	{
		if ((go->y0 + 5) > (MAP_H - 300) || (go->y1 + 5) > (MAP_H - 300))
			return (1);
		go = go->next;
	}
	return (0);
}

int			check_movement(t_window *window, t_coords *lines, int key)
{
	if (window->block == 1)
	{
		if (key == 124)
			return (check_right(lines));
		if (key == 123)
			return (check_left(lines));
		if (key == 126)
			return (check_up(lines));
		if (key == 125)
			return (check_down(lines));
	}
	return (0);
}
