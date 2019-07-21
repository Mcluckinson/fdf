/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_works.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:24:17 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/21 15:26:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	set_up_window(t_map *map, t_window *window)
{
	//t_window	*window;

//	window = (t_window*)malloc(sizeof(t_window));
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, map->x_max - map->x_min + 1, map->y_max - map->y_min + 1, "FDF");
	window->img_ptr = mlx_new_image(window->mlx_ptr, map->x_max - map->x_min + 1, map->y_max - map->y_min + 1);
	window->linesize = (int*)malloc(sizeof(int));
	*window->linesize = (map->x_max - map->x_min + 1) * UNIQ_BPP;
	window->depth = (int*)malloc(sizeof(int));
	*window->depth = UNIQ_BPP * 8;
	window->endian = (int*)malloc(sizeof(int));
	*window->endian = 0;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->endian);
	return ;
}
