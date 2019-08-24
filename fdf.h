/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:15:36 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/24 11:45:12 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include "libft/libft.h"
#include <math.h>
#define UNIQ_BPP 4
#define MAP_H 1300
#define MAP_W 2000

typedef	struct		s_lines////////////СТРОЧКИ КАРТЫ
{
	char 			*line;
	struct s_lines	*next;
}					t_lines;

typedef	struct		s_map/////////КАРТА
{
	int				x;
	int				y;
	int				**z;
	int 			x_max;
	int 			y_max;
	int 			x_min;
	int 			y_min;
	int 			z_max;
	int 			z_min;
}					t_map;

typedef	struct		s_coords////////ЛИНИИ ДЛЯ РИСОВАНИЯ
{
	int				x0;
	int 			x1;
	int				y0;
	int 			y1;
	int				z0;
	int 			z1;
	int 			z0orig;
	int 			z1orig;
	struct s_coords	*next;
	unsigned int	color_start;
	unsigned int 	color_finish;
}					t_coords;

typedef	struct		s_window/////////СТРУКТУРА СО ВСЕМИ ССЫЛКАМИ И ДАННЫМИ
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char 	*img_data;
	int 	*endian;
	int 	*linesize;
	int 	*depth;
	int 	fd;
	t_map	*map;
	t_lines	*start;
	t_coords	*lines;
	t_coords	*turned;
	t_coords	*current;
	float 		cur_zoom;
	int 		cur_x;
	int 		cur_y;
	int 		block;
	int 		height_mod;
	int 		gradient_mod;
	int 		projection;
	unsigned int color[2];
}					t_window;


void	gradient1(t_window *window);
void	gradient2(t_window *window);
void	gradient3(t_window *window);
void				pre_draw_line(int coord[4], t_coords *line);
void	inter_via_mass(int coord[4], int inter[4]);
int 				check_shit(int ixy[3], int *steep);
void				draw_line(t_coords *line, t_window *window);


t_lines		*read_lines(int fd);
void		del_lines(t_lines *start);
t_map	*read_map(t_lines *start);
int 	check_errors(t_map *map);
void	del_map(t_map *map);
int 	**find_z(t_lines *start, int x, int y);
int 	find_x(t_lines *start);
int 		find_y(t_lines *start);
void	draw_line(t_coords *line, t_window *window);
//void	swap_em(int *a0, int *a1);
t_coords	*get_lines(t_map *map);
t_coords	*new_coords(t_coords *coords);
t_coords	*get_horisontal(t_coords *line, t_map *map);
t_coords	*get_vertical(t_coords *line, t_map *map);
t_coords	*fix_orig(t_coords *start, float ratio);
int	draw_map(t_coords *lines, t_window *window);
void put_color(char *img_data, int i, unsigned int color);
int 	*steep_check(int *x0, int *x1, int *y0, int *y1);
int	set_up_window(t_window *window, char *map_name);
int 	find_i(int x, int y, t_window *window ,int *steep);
t_coords	*iso(t_coords *start, t_map *map, t_window *window);
void	find_max_min(t_coords *turned, t_map *map);
t_coords	*move_position(t_coords *start, t_map *map);
t_coords	*resize_all(t_coords *start, t_map *map);
void	del_coords(t_coords *lines);
t_coords	*new_coords_from_above(t_coords *coords);
int close_window(t_window *window);
int key_press(int key, t_window *window);
void	del_win(t_window *window);
void	draw_parallel(t_window *window);
t_coords	*parallel(t_coords *start, t_map *map, t_window *window);
void 	draw_iso(t_window *window);
void	print_controls(t_window *window);
void 	move_right(t_window *window);
void 	move_left(t_window *window);
void 	move_down(t_window *window);
void 	move_up(t_window *window);
void	zoom_in(t_window *window);
void	zoom_out(t_window *window);
void	copy_to_current(t_coords *origin, t_coords *target);
void	fix_current(t_coords *start, t_coords *target, float ratio, t_window *window);
t_coords	*init_current(t_window *window);
void	move(int key, t_window *window);
int mouse_buttons(int key, int x, int y, t_window *window);
double percent(int start, int end, int current);
int get_light(unsigned int start, unsigned int end, double percentage);
unsigned int get_color(int cur_x, t_coords *line, int *steep);
void	randomise_colors(t_window *window);
void	redraw_altitude(t_window *window);
void	change_altitude(int key, t_window *window);

///TRYINA ADD HEIGHT GRADIENT
unsigned int get_color_z(int cur_x, t_coords *line, int *steep);
void	change_gradient(t_window *window);

#endif