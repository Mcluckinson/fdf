/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:37:42 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/25 21:40:17 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
///ТУТ ВСЕ ПРОСТО, ПОКА НЕ ЗАКОНЧАТСЯ ЭЛЕМЕНТЫ СТРУКТУРЫ t_coords, будет к каждому запускать DRAW_LINE
int	draw_map(t_coords *lines, t_window *window)
{

	t_coords	*go;

	go = lines;
	if (window->gradient_mod == 1)
		find_max_min_z(go, window);
//	recolor_map(go, window);
	ft_bzero(window->img_data, MAP_W * UNIQ_BPP * (MAP_H - 300));
	while (go != NULL)
	{
		draw_line(go, window, window->lines);
		go = go->next;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);//MLX ФУНКЦИЯ, КОТОРАЯ КИДАЕТ ИЗОБРАЖЕНИЕ НА ЭКРАН
	return (0);
}

/*void	recolor_map(t_coords *lines, t_window *window)
{
	t_coords *go;

	go = lines;
	if (window->gradient_mod == 1)
	{
		while (go != NULL)
		{
			recolor_line(go, window);
			go = go->next;
		}
	}
	else
	{
		while (go != NULL)
		{
			recolor_back(go, window);
			go = go->next;
		}
	}
}*/