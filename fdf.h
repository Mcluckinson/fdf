/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:15:36 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/15 13:16:42 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include "libft/libft.h"
#include <math.h>
#define UNIQ_BPP 4

typedef	struct		s_lines
{
	char 			*line;
	struct s_lines	*next;
}					t_lines;

typedef	struct		s_map
{
	int				x;
	int				y;
	int				**z;
}					t_map;

typedef	struct		s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char 	*img_data;
	int 	*endian;
	int 	*linesize;
	int 	*depth;
	int 	width;
	int 	height;
}					t_window;

typedef	struct		s_coords
{
	int				x0;
	int 			x1;
	int				y0;
	int 			y1;
	int				z0;
	int 			z1;
	struct s_coords	*next;
}					t_coords;


t_lines		*read_lines(int fd);
void		del_lines(t_lines *start);
t_map	*read_map(t_lines *start);
int 	check_errors(t_map *map);
void	del_map(t_map *map);
int 	**find_z(t_lines *start, int x, int y);
int 	find_x(t_lines *start);
int 		find_y(t_lines *start);
void	draw_line(t_coords *line, t_window *window);
void	swap_em(int *a0, int *a1);
t_coords	*get_lines(t_map *map);
t_coords	*new_coords(t_coords *coords);
t_coords	*get_horisontal(t_coords *line, t_map *map);
t_coords	*get_vertical(t_coords *line, t_map *map);
t_coords	*fix_orig(t_coords *start);
void	draw_map(t_coords *lines, t_window *window);
char *put_color(char *img_data, int i, int color);
int 	steep_check(int *x0, int *x1, int *y0, int *y1);
t_window	*set_up_window(int win_width, int win_height);
int 	find_i(int x, int y, t_window *window ,int steep);
t_coords	*iso(t_coords *start);

#endif