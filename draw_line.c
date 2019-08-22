/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 17:38:21 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/21 19:50:49 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*void	swap_em(int *a0, int *a1)
{
	int c;

	c = *a0;
	*a0 = *a1;
	*a1 = c;
}*/
/////МЕНЯЕТ МЕСТАМИ КООРДИНАТЫ ДЛЯ КОРРЕКТНОГО РИСОВАНИЯ, ФИКСИРУЕТ ИЗМЕНЕНИЯ В int *steep
/////int *steep хранит два инта, steep[0] фикстирует первое изменение, steep[0] фиксирует второе
int 	*steep_check(int *x0, int *x1, int *y0, int *y1)
{
	int	*steep;

	steep = (int*)malloc(sizeof(int) * 2);
	steep[0] = 0;
	steep[1] = 0;
	if (labs(*y1 - *y0) > labs(*x1 - *x0))
	{
		steep[0]++;
	//	swap_em(x0, y0);
	//	swap_em(x1, y1);
		ft_swap(x0, y0);
		ft_swap(x1, y1);
	}
	if (*x0 > *x1)
	{
		steep[1]++;
	//	swap_em(x0, x1);
	//	swap_em(y0, y1);
		ft_swap(x0, x1);
		ft_swap(y0, y1);
	}
	return (steep);
}

void	draw_line(t_coords *line, t_window *window)
{
	int x0[1];///УКАЗАТЕЛИ НА КООРДИНАТЫ, НУЖНЫ, ЧТОБЫ МОЖНО БЫЛО МЕНЯТЬ ИХ ЗНАЧЕНИЕ
	int x1[1];
	int y0[1];
	int y1[1];
	int	dx;/////ДЕЛЬТА ИКС
	int	dy;///////ДЕЛЬТА У
	int error; //////КОЭФФИЦИЕНТ ОШИБКИ
	int x; /////ТЕКУЩИЙ Х ВНУТРИ ОДНОЙ ЛИНИИ
	int y;/////ТЕУЩИЙ У ВНУТРИ ОДНОЙ ЛИНИИ
	int ystep; //////ЗНАЧЕНИЕ ИЗМЕНИЯ У (ВВЕРХ 1, ВНИЗ -1, ТОЧКА 0:0 НАХОДИТСЯ В ВЕРХНЕМ ЛЕВОМ УГЛУ!!!)
	unsigned int	final_color; /////ЦВЕТ КОТОРЫЙ БУДЕТ КЛАСТЬСЯ В КОНКРЕТНЫЙ ПИКСЕЛЬ, ВЫСЧИТЫВАЕТСЯ ДАЛЬШЕ
	int 	i; ////ЭТИМ Я ЛЕЗУ В НУЖНЫЙ ПИКСЕЛЬ, НАПРИМЕР img_data[i] при i = 0 - это самый первый пиксель в верхнем левом углу, i = 4 - следующий, справа от него
	int 	*steep;/////ДАТЧИК НАКЛОНА, ОПИСАН ВЫШЕ
///КЛАДУ В УКАЗАТЕЛИ КООРДИНАТЫ ТЕКУЩЕЙ ЛИНИИ
	*x0 = line->x0;
	*x1 = line->x1;
	*y0 = line->y0;
	*y1 = line->y1;

////МЕНЯЮ МЕСТАМИ КООРДИНАТЫ ПРИ НЕОБХОДИМОСТИ
	steep = steep_check(x0, x1, y0, y1);
	dx = *x1 - *x0;
	dy = labs(*y1 - *y0);
	error = dx/2;////////ЭТО Я ПРОСТО СПИЗДИЛ В ОБЩЕМ-То
	if (*y0 < *y1) ///////ОПРЕДЕЛЯЮ НАКЛОН ПО У
		ystep = 1;
	else if (*y0 > *y1)
		ystep = -1;
	y = *y0; /////ЭТО ТЕКУЩИЕ КООРДИНАТЫ. НАЧИНАЮ С ТОЧКИ Х0:У0
	x = *x0;
	while (x <= *x1) /////И ИДУ ПО ИКСУ
	{
		if (window->gradient_mod == 0) /////////ПРОВЕРЯЮ КАКОЙ ВИД ГРАДИЕНТА ВКЛЮЧЕН И В ЗАВИСИМОСТИ ОТ ЭТОГО КЛАДУ ЦВЕТА
			final_color = get_color(x, line, steep);/////ВОТ ЗДЕСЬ КЛАДУ ЦВЕТА
		else if (window->gradient_mod == 1)
			final_color = get_color_z(x, line, steep); ////ИЛИ ЗДЕСЬ
		if ((x >= 0 && x <= MAP_W && y > 0 && y <= MAP_H - 300 && steep[0] == 0) ||
				(y >= 0 && y <= MAP_W && x > 0 && x <= MAP_H - 300 && steep[0] == 1))  //////ЭТОТ ИФ НЕ ДАЕТ РИСОВАТЬ НИЧЕГО, ЧТО ВЫЛЕЗЛО ЗА ПРЕДЕЛЫ ЭКРАНА
		{
			i = find_i(x, y, window, steep); ///////ЭТА ФУНКЦИЯ НАХОДИТ НУЖНЫЙ ПИКСЕЛЬ В ЗАВИСИМОСТИ ОТ ТЕКУЩЕГО Х И У
			put_color(window->img_data, i, final_color); /////////КЛАДЕТ ЦВЕТ 1 ПИКСЕЛЯ В char *img_data[i]
		}
		error -= dy;//////МЕНЯЕТ КОЭФФИЦИЕНТ ОШИБКИ СМ ДАЛЬШЕ
		if (error < 0) ///КАК ТОЛЬКО КОЭФФИЦИЕНТ ОШИБКИ СТАНОВИТСЯ < 0 МЫ меняем У. ЭТО И ЕСТЬ ФИШЕЧКА В АЛГОРИТМЕ БРЕЗЕНХЕМА
		{
			y = y + ystep;
			error = error + dx; ////МЕНЯЕМ КОЭФФ ОШИБКИ ПО АЛГОРИТМУ
		}
		x++;
	}
	free(steep);/////ЧИСТИМ СТИП
}

int 	find_i(int x, int y, t_window *window ,int *steep)
{
	int i;

	if (steep[0] == 0)
		i = (x  * (*window->depth / 8)) + (y * (*window->linesize));////ПРОСТО ПОДСТАВЬ КАКИЕ НИБУДЬ Х и У и посмотри, что получится. НА КАЖДЫЙ ПИКСЕЛЬ 4 БАЙТА!
	else
		i = (y * (*window->depth / 8)) + (x * (*window->linesize));
	return (i);
}
////////КЛАДЕТ ЦВЕТ В char *img_data. 4 БАЙТА ЭТО ЗДЕСЬ
void	put_color(char *img_data, int i, unsigned int color)
{
	img_data[i] = color; // B — Blue
	img_data[++i] = color >> 8; // G — Green
	img_data[++i] = color >> 16; // R — Red
//	img_data[++i] = 0; // Alpha channel ///////ТУТ И ТАК ЛЕЖАТ 0, поэтому это лишнее
}
/////ЭТО ДЛЯ ГРАДИЕНТА, ОПРЕДЕЛЯЕТ ПРОЦЕНТНОЕ СООТНОШЕНИЕ ТЕКУЩЕЙ ТОЧКИ В ЛИНИИ
double percent(int start, int end, int current)
{
	double placement;
	double distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}
////////ОПРЕДЕЛЯЕТ ЦВЕТ В ПРОЦЕНТНОМ СООТНОШЕНИИ, БЕРЯ ДВА ЦВЕТА (НАЧАЛЬНЫЙ И КОНЕЧНЫЙ)
int get_light(unsigned int start, unsigned int end, double percentage)
{
	return ((unsigned int)((1 - percentage) * start + percentage * end));
}
///////////ЭТА ШТУКА ДЕЛАЕТ ГРАДИЕНТ КАЖДОЙ ЛИНИИ
unsigned int get_color(int cur_x, t_coords *line, int *steep)
{
	unsigned int     red;
	unsigned int     green;
	unsigned int     blue;
	double  percentage;

	if (line->color_start == line->color_finish)
		return (line->color_start);
	if (steep[0] == 0)
		percentage = percent(line->x0, line->x1, cur_x);
	else
		percentage = percent(line->y0, line->y1, cur_x);
	red = get_light((line->color_start >> 16) & 0xFF, (line->color_finish >> 16) & 0xFF, percentage);
	green = get_light((line->color_start >> 8) & 0xFF, (line->color_finish >> 8) & 0xFF, percentage);
	blue = get_light(line->color_start & 0xFF, line->color_finish & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
////////ЭТА ШТУКА ДЕЛАЕТ ГРАДИЕНТ В ЗАВИСИМОСТИ ОТ ВЫСОТЫ
unsigned int get_color_z(int cur_x, t_coords *line, int *steep)
{
	unsigned int     red;
	unsigned int     green;
	unsigned int     blue;
	double  percentage;

	if (line->color_start == line->color_finish)
		return (line->color_start);
	if (line->z0 == line->z1)
	{
		if (line->z0 == 0)
			return (line->color_finish);
		else
			return (line->color_start);
	}
	if (steep[1] == 0)
		percentage = percent(line->y0, line->y1, cur_x);
	else
		percentage = percent(line->y1, line->y0, cur_x);
	red = get_light((line->color_start >> 16) & 0xFF, (line->color_finish >> 16) & 0xFF, percentage);
	green = get_light((line->color_start >> 8) & 0xFF, (line->color_finish >> 8) & 0xFF, percentage);
	blue = get_light(line->color_start & 0xFF, line->color_finish & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}