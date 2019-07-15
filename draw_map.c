/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/13 18:23:11 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_coords *lines, t_window *window)
{
	while (lines->next != NULL)
	{
		draw_line(lines, window);
		lines = lines->next;
	}
}