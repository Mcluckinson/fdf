/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 13:59:02 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/21 13:57:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
///МАЛЛОЧИМ t_lines и кладем туда считанное gnl
t_lines		*read_lines(int fd)
{
	t_lines		*start;
	t_lines		*another;

	if (!(start = (t_lines*)malloc(sizeof(t_lines))))
		return (NULL);
	another = start;
	while (get_next_line(fd, &another->line) != 0)
	{
		if (!(another->next = (t_lines*)malloc(sizeof(t_lines))))
			del_lines(start);
		another = another->next;
	}
	another->next = NULL;
	return (start);
}
//УДАЛЯЛАКА ДЛЯ t_lines
void		del_lines(t_lines *start)
{
	while (start->next != NULL)
	{
		del_lines(start->next);
		start->next = NULL;
	}
	free(start->line);
	free(start);
}
//СЧИТАЕТ КОЛИЧЕСТВО СТРОК, ЭТО БУДЕТ У
int 		find_y(t_lines *start)
{
	int y;
	t_lines	*temp;

	temp = start;
	y = 0;
	while (temp->next)
	{
		y++;
		temp = temp->next;
	}
	return (y);
}
///СТРСПЛИТОМ ДЕЛИТ СТРОКУ, СЧИТАЕТ КОЛИЧЕСТВО ЭЛЕМЕНТОВ, ЁТО БУДЕТ Х
int 	find_x(t_lines *start)
{
	int x;
	int x_max;//ДЛЯ ПРОВЕРКИ КОЛИЧЕСТВА ЭЛЕМЕНТОВ В СТРОКАХ
	t_lines *temp;
	char **split;

	x = 0;
	x_max = 0;
	temp = start;
	while (temp->next)
	{
		x = 0;
		split = ft_strsplit(temp->line, ' ');
		while (split[x])
		{
			free(split[x]);
			x++;
		}
		free(split);
		if (!x_max)
			x_max = x;
		else if (x != x_max)
			return (0);///СРАВНИВАЕТ КОЛИЧЕСТВО Х В СЧИТАННОЙ СТРОКЕ С КОЛИЧЕСТВОМ Х В ПРЕДЫДУЩИХ, ОНО ДОЛЖНО БЫТЬ ОДИНАКОВЫМ
		temp = temp->next;
	}
	return (x);
}
///СЧИТЫВАЕТ ВЫСОТЫ, КЛАДЕТ В **Z
int 	**find_z(t_lines *start, int x, int y)
{
	int	**z;
	int yy;
	int i;
	char **split;
	t_lines	*temp;

	temp = start;
	yy = 0;
	if (!(z = (int**)malloc(sizeof(int*) * (y + 1))))
		return (NULL);
	while (yy < y)
	{
		i = 0;
		split = ft_strsplit(temp->line, ' ');
		z[yy] = (int*)malloc(sizeof(int) * x);
		while (i < x)
		{
			z[yy][i] = ft_atoi(split[i]);
			free(split[i]);
			i++;
		}
		free(split);
		yy++;
		temp = temp->next;
	}
	return (z);
}
///УДАЛЯЛКА ДЛЯ КАРТЫ
void	del_map(t_map *map)
{
	int i;

	i = 0;
	if (map->z != NULL)
	{
		while (i < map->y)
		{
			free(map->z[i]);
			i++;
		}
		free(map->z);
	}
	free(map);
}
////ПРОВЕРКА ОШИБОК, НУЖНО ДОПОЛНИТЬ
int 	check_errors(t_map *map)
{
	if (!map->x || !map->y || !map->z)
		return (0);
	return (1);
}
////ЧИТАЕТ КАРТУ В t_map *map. ИСПОЛЬЗУЕТ ФУНКЦИИ ВЫШЕ
t_map	*read_map(t_lines *start)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->x_max = 0;
	map->y_max = 0;
	map->x_min = 0;
	map->y_min = 0;
	map->y = find_y(start);
	map->x = find_x(start);
	map->z = find_z(start, map->x, map->y);
	if (!check_errors(map))
	{
		del_lines(start);
		del_map(map);
		return (NULL);
	}
	return (map);
}
