/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/15 14:02:48 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	int fd;
	t_lines	*start;
	t_map	*map;
	t_coords	*lines;
	t_coords	*turned;
	t_window	*window;

	argc = 1;
	fd = open (argv[argc], O_RDONLY);
	start = read_lines(fd);
	map = read_map(start);
	lines = get_lines(map);
	turned = iso(lines);
	window = set_up_window(map->x * 40, map->y * 40);
	draw_map(turned, window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 50, 100);
	mlx_loop(window->mlx_ptr);
	close (fd);
	return (0);
}