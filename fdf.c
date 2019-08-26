/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 14:28:37 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/24 22:33:26 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
////ЧИСТИТ ВСЕ, ЧТО НАЙДЕТ
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
	if (window->current)
		del_coords(window->current);
	if (window->map)
		del_map(window->map);
	free(window);
}

int		main(int argc, char **argv)
{
	static t_window	*window;//СТАТИК НУ ЧТОБ НАВЕРНЯКА

	argc = 1;//КОСТЫЛЬ
	if (!(window = (t_window*)malloc(sizeof(t_window))))
		return (0);
	if (!(window->fd = open (argv[argc], O_RDONLY)) ||
			!(window->start = read_lines(window->fd)) ||//ЧИТАЕТ КАРТУ ПО СТРОЧКАМ, ГНЛ, КЛАДЕТ В МАССИВ t_lines
			!(window->map = read_map(window->start)) ||//ДОСТАЕТ ДАННЫЕ(высоты, ширина, высота) ИЗ СТРОК, кладет в t_map
			!(window->lines = get_lines(window->map)))//CОБИРАЕТ ЛИНИИ ИЗ БАЗОВЫХ КООРДИНАТ, структура t_coords window->lines
	{
		del_win(window);
		return (0);
	}
	if (set_up_window(window, argv[argc]) == -1) //СОЗДАЕТ ВСЕ ОСТАЛЬНЫЕ ДАННЫЕ В t_window *window
		return (0);
	close (window->fd);
	window->turned = iso(window->lines, window->map, window);//ПРЕОБРАЗУЕТ window->lines в изометрическую проекцию, кладет в t_coords window->turned

	window->current = init_current(window);//СОЗДАЕТ t_window *current, оттуда все и рисуется. Сейчас в нем нет данных, количество элементов такое же, как количество линий
	copy_to_current(window->turned, window->current);//КОПИРУЕТ ДАННЫЕ ИЗ t_coords turned в t_coords current
	move_position(window->current, window->map);//ДВИГАЕТ t_coords current в центр экрана
	draw_map(window->current, window);//РИСУЕТ КАРТУ НА ЭКРАНЕ
	mlx_hook(window->win_ptr, 17, 1L<<17, close_window, window); //ОТСЛЕЖИВАЕТ НАЖАТИЕ КРАСНОЙ КНОПКИ ДЛЯ ЗАКРЫТИЯ FDF
	mlx_hook(window->win_ptr, 4, 1L<<2, mouse_buttons, window); //ОТСЛЕЖИВАЕТ НАЖАТИЕ КНОПОК МЫШИ
	mlx_hook(window->win_ptr, 2, 1L<<0, key_press, window);//ОТСЛЕЖИВАЕТ НАЖАТИЕ КЛАВИШ
	mlx_loop(window->mlx_ptr);//ПУСКАЕТ ПРОГРАММУ В БЕСКОНЕЧНЫЙ ЦИКЛ
	return (0);
}