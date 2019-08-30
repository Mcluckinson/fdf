/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_works.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:24:17 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 14:11:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			set_up_window(t_window *window, char *map_name)
{
	char	*name;

	name = ft_strjoin("FDF ", map_name);
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, MAP_W, MAP_H, name);
	free(name);
	window->cur_zoom = 1;
	window->img_ptr = mlx_new_image(window->mlx_ptr, MAP_W, MAP_H - 300);
	if (check_set_up(window) == 0)
	{
		del_win(window);
		return (-1);
	}
	*window->linesize = MAP_W * UNIQ_BPP;
	*window->depth = UNIQ_BPP * 8;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth,
			window->linesize, window->endian);
	print_controls(window);
	window->block = 1;
	window->color[0] = 0x0011A953;
	window->color[1] = 0x00ff00ff;
	window->projection = 2;
	window->fix_ratio = 1;
	return (0);
}

int			check_set_up(t_window *window)
{
	if (!(window->linesize = (int*)malloc(sizeof(int))))
		return (0);
	if (!(window->depth = (int*)malloc(sizeof(int))))
		return (0);
	if (!(window->endian = (int*)malloc(sizeof(int))))
		return (0);
	return (1);
}

void		print_controls(t_window *window)
{
	char	*ist;

	ist = "press '1' for parallel, press '2' for isometric projection";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1100, 0xffffff, ist);
	ist = "press ESC or red X to exit";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1150, 0xffffff, ist);
	ist = "arrows to move, LMB + mouse move to turn around";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1200, 0xffffff, ist);
	ist = "NUM +/-  or MOUSE WHEEL for zoom";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 50, 1250, 0xffffff, ist);
	ist = "W & S to change altitude";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1100, 0xffffff, ist);
	ist = "NUM 1-9 for turning";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1150, 0xffffff, ist);
	ist = "SPACE blocks movement";
	different_gradients(window, ist);
}

void		different_gradients(t_window *window, char *ist)
{
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1200, 0xffffff, ist);
	ist = "press 0 to go mad";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 800, 1250, 0xffffff, ist);
	ist = "press 4 to change color mod";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1300, 1100, 0xffffff, ist);
	ist = "press 5 to behold sunset";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1300, 1150, 0xffffff, ist);
	ist = "press 6 to see tropicana";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1300, 1200, 0xffffff, ist);
	ist = "press 7 for vodka with cranberry";
	mlx_string_put(window->mlx_ptr, window->win_ptr, 1300, 1250, 0xffffff, ist);
}
