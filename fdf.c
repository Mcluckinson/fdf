/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/30 14:11:32 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		continue_del_win(t_window *window)
{
	if (window->turned)
		del_coords(window->turned);
	if (window->endian)
		free(window->endian);
	if (window->depth)
		free(window->depth);
	if (window->img_data)
		free(window->img_data);
	if (window->current)
		del_coords(window->current);
	if (window->map)
		del_map(window->map);
}

void			del_win(t_window *window)
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
	continue_del_win(window);
	free(window);
}

static int		preparations(t_window *window, char *name)
{
	ft_bzero(window, sizeof(t_window));
	if (!(window->fd = open(name, O_RDONLY)) ||
		!(window->start = read_lines(window->fd)) ||
		!(window->map = read_map(window->start)) ||
		!(window->lines = get_lines(window->map)))
	{
		del_win(window);
		return (0);
	}
	if (set_up_window(window, name) == -1)
		return (0);
	close(window->fd);
	return (1);
}

int				main(int argc, char **argv)
{
	t_window	*window;

	if (argc != 2)
	{
		printf("Incorrect input :(");
		return (-1);
	}
	else
	{
		if (!(window = (t_window*)malloc(sizeof(t_window)))
		|| !(preparations(window, argv[1])))
			return (print_error(1));
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
