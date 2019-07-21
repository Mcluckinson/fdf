/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/21 15:36:39 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_window	*window;

	argc = 1;
	window = (t_window*)malloc(sizeof(t_window));
	window->fd = open (argv[argc], O_RDONLY);
	window->start = read_lines(window->fd);
	window->map = read_map(window->start);
	if (!(window->lines = get_lines(window->map)))
	{
		del_map(window->map);
		printf ("failed to get lines\n");
		close(window->fd);
		return (0);
	}
	close (window->fd);
	window->turned = iso(window->lines, window->map);
	set_up_window(window->map, window);
	draw_map(window->turned, window);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img_ptr, 0, 0);
	mlx_key_hook(window->win_ptr, key_press, NULL);
	mlx_loop(window->mlx_ptr);
	return (0);
}