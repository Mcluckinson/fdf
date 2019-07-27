/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_works.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:24:17 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/27 16:47:07 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	set_up_window(t_window *window, char *map_name)
{
	char *name;
	name = ft_strjoin("FDF ", map_name);
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, MAP_W, MAP_H, name);
	free(name);
//	window->img_ptr = mlx_new_image(window->mlx_ptr, map->x_max - map->x_min + 1, map->y_max - map->y_min + 1);
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H - 300);
	if (!(window->linesize = (int*)malloc(sizeof(int))) || !(window->depth = (int*)malloc(sizeof(int))) ||
		!(window->endian = (int*)malloc(sizeof(int))))
	{
		del_win(window);
		return (-1);
	}
//	*window->linesize = (map->x_max - map->x_min + 1) * UNIQ_BPP;
	*window->linesize = MAP_W * UNIQ_BPP;
	*window->depth = UNIQ_BPP * 8;
	*window->endian = 0;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->endian);
//	window->img_data = (int*)mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->endian);
	print_controls(window);
	return (0);
}

void	print_controls(t_window *window)
{
	char *instr;

	instr = "press '1' for parallel, press '2' for isometric projection";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1100, 0x00ffffff, instr);
	instr = "press ESC or red X to exit";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1150, 0x00ffffff, instr);
	instr = "arrows to move, LMB + mouse move to turn around";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1200, 0x00ffffff, instr);
	instr = "mouse wheel for zoom";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1250, 0x00ffffff, instr);
}