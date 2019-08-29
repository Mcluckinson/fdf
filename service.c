/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 20:47:24 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/29 20:47:24 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*init_current(t_window *window)
{
	t_coords	*result;
	t_coords	*go;

	go = window->turned;
	result = window->current;
	while (go != NULL)
	{
		result = new_coords_from_above(result);
		go = go->next;
	}
	return (result);
}

void	copy_to_current(t_coords *origin, t_coords *target)
{
	t_coords *go;
	t_coords *change;

	go = origin;
	change = target;
	while (go != NULL)
	{
		change->x0 = go->x0;
		change->x1 = go->x1;
		change->y0 = go->y0;
		change->y1 = go->y1;
		change->z0 = go->z0;
		change->z1 = go->z1;
		change->color_start = go->color_start;
		change->color_finish = go->color_finish;
		go = go->next;
		change = change->next;
	}
}

void	fix_current(t_coords *start, t_coords *target, float ratio, t_window *window)
{
	if (start != NULL)
	{
		fix_current(start->next, target->next, ratio, window);
		target->x0 = (start->x0 * ratio + (5 * window->cur_x)) ;
		target->x1 = (start->x1 * ratio + (5 * window->cur_x));
		target->y0 = (start->y0 * ratio + (5 * window->cur_y));
		target->y1 = (start->y1 * ratio + (5 * window->cur_y));
		target->z0 = start->z0 * ratio;
		target->z1 = start->z1 * ratio;
	}
	return ;
}
