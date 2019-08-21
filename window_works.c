/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_works.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:24:17 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/21 15:21:24 by cyuriko          ###   ########.fr       */
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
	window->cur_zoom = 1;
	window->current = NULL;
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H - 300);
	if (!(window->linesize = (int*)malloc(sizeof(int))) || !(window->depth = (int*)malloc(sizeof(int))) ||
		!(window->endian = (int*)malloc(sizeof(int))))
	{
		del_win(window);
		return (-1);
	}
	*window->linesize = MAP_W * UNIQ_BPP;
	*window->depth = UNIQ_BPP * 8;
	*window->endian = 0;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->endian);
	print_controls(window);
	window->cur_x = 0;
	window->cur_y = 0;
	window->block = 1;
	window->height_mod = 0;
	window->gradient_mod = 0;
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
	instr = "NUM +/-  or MOUSE WHEEL for zoom";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1250, 0x00ffffff, instr);
	instr = "W & S to change altitude";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1100, 0x00ffffff, instr);
	instr = "NUM 1-9 for turning";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1150, 0x00ffffff, instr);
	instr = "SPACE blocks movement";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1200, 0x00ffffff, instr);
	instr = "press 0 to go mad";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1250, 0x00ffffff, instr);
	instr = "press 4 to change color mod";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1300, 1100, 0x00ffffff, instr);
}