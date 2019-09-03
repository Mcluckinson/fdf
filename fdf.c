/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/03 13:09:09 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		continue_del_win(t_window *window)
{
	if (window && window->turned)
		del_coords(window->turned);
	if (window && window->endian)
		free(window->endian);
	if (window && window->depth)
		free(window->depth);
	if (window && window->img_data)
		free(window->img_data);
	if (window && window->current)
		del_coords(window->current);
	if (window && window->map)
		del_map(window->map);
}

void			del_win(t_window *window)
{
	if (window && window->fd)
		close(window->fd);
	if (window && window->win_ptr)
		free(window->win_ptr);
	if (window && window->start)
		del_lines(window->start);
	if (window && window->mlx_ptr)
		free(window->mlx_ptr);
	if (window && window->img_ptr)
		free(window->img_ptr);
	if (window && window->linesize)
		free(window->linesize);
	if (window && window->lines)
		del_coords(window->lines);
	continue_del_win(window);
	if (window)
		free(window);
}

static int		preparations(t_window *window, char *name)
{
	ft_bzero(window, sizeof(t_window));
	if (!(window->fd = open(name, O_RDONLY)))
		print_error(2, window);
	if (window->fd == -1)
		print_error(3, window);
	if (!(window->start = read_lines(window->fd)))
		print_error(3, window);
	if (!(window->map = read_map(window->start, window)))
		print_error(2, window);
	if (!(window->lines = get_lines(window->map)))
		print_error(5, window);
	if (set_up_window(window, name) == -1)
		print_error(1, window);
	close(window->fd);
	return (1);
}

int				main(int argc, char **argv)
{
	t_window	*window;

	window = NULL;
	if (argc != 2)
		print_error(4, window);
	else
	{
		if (!(window = (t_window*)malloc(sizeof(t_window)))
		|| !(preparations(window, argv[1])))
			return (0);
		window->turned = iso(window->lines, window);
		window->current = init_current(window);
		copy_to_current(window->turned, window->current);
		move_position(window->current, window->map);
		draw_map(window->current, window);
		mlx_hook(window->win_ptr, 17, 1L << 17, close_window, window);
		mlx_hook(window->win_ptr, 4, 1L << 2, mouse_buttons, window);
		mlx_hook(window->win_ptr, 2, 1L << 0, key_press, window);
		mlx_loop(window->mlx_ptr);
	}
	return (0);
}
