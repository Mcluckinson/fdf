/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/27 19:46:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	del_win(t_window *window)
{
	if (window->fd)
		close(window->fd);
	if (window->win_ptr)
		free(window->win_ptr);
	if (window->start)
		del_lines(window->start);
	if (window->mlx_ptr)
		free(window->mlx_ptr);
	if (window->img_ptr)
		free(window->img_ptr);
	if (window->linesize)
		free(window->linesize);
	if (window->lines)
		del_coords(window->lines);
	if (window->turned)
		del_coords(window->turned);
	if (window->endian)
		free(window->endian);
	if (window->depth)
		free(window->depth);
	if (window->img_data)
		free(window->img_data);
	if (window->map)
		del_map(window->map);
	free(window);
}

int		main(int argc, char **argv)
{
	static t_window	*window;

	argc = 1;
	if (!(window = (t_window*)malloc(sizeof(t_window))))
		return (0);
	if (!(window->fd = open (argv[argc], O_RDONLY)) ||
			!(window->start = read_lines(window->fd)) ||
			!(window->map = read_map(window->start)) ||
			!(window->lines = get_lines(window->map)))
	{
		del_win(window);
		return (0);
	}
	close (window->fd);
	window->turned = iso(window->lines, window->map);
	if (set_up_window(window, argv[argc]) == -1)
		return (0);
	draw_map(window->turned, window);
	mlx_hook(window->win_ptr, 17, 1L<<2, close_window, window);
	mlx_hook(window->win_ptr, 3, 1L<<0, key_press, window);
//	mlx_key_hook(window->win_ptr, key_press, window);
	mlx_loop(window->mlx_ptr);
	return (0);
}