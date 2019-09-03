/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 13:59:02 by cyuriko           #+#    #+#             */
/*   Updated: 2019/09/03 15:47:08 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_lines		*read_lines(int fd)
{
	t_lines		*start;
	t_lines		*another;
	int 		gnl;
	char 		*temp;

	gnl = 1;
	start = NULL;
	another = NULL;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &temp);
		if (gnl == 1)
		{
			if (!(another = add_lines(another)))
				return (NULL);
			if (start == NULL)
				start = another;
			another->line = ft_strdup(temp);
			free (temp);
		}
		else if (gnl == 0)
			break;
		else
			del_lines(start);
	}
	return (start);
}

t_lines		*add_lines(t_lines *line)
{
	t_lines *start;

	if (!(start = (t_lines*)malloc(sizeof(t_lines))))
		return (NULL);
//	if (line == NULL)
		start->next = NULL;
	if (line != NULL)
		line->next = start;
	return (start);
}
//	if (!(start = (t_lines*)malloc(sizeof(t_lines))))
//		return (NULL);
//	start->next = NULL;
//	another = start;
//	while (get_next_line(fd, &another->line) /*&& another->next*/)/* && gnl != 0 && gnl != -1*/
/*	while (gnl == 1)
	{
		gnl = get_next_line(fd, &temp);
		if (gnl == 1)
		{
			another->line = ft_strdup(temp);
			free(temp);
		}

		if (!(another->next = (t_lines *) malloc(sizeof(t_lines))))
				del_lines(start);
		if (another->next)
		{
			another = another->next;
			another->next = NULL;
		}
	}
	if (get_next_line(fd, &another->line) == 0)
	{
		free (another->next);
		free (another);

		another = NULL;
	}
	else if (get_next_line(fd, &another->line) == -1)
	{
		del_lines(start);
		return (NULL);
	}
	return (start);
}*/

void		del_lines(t_lines *start)
{
	if (start)
		del_lines(start->next);
	if (start != NULL && start->line != NULL)
		free(start->line);
	free(start);
}

void		del_map(t_map *map)
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

int			check_errors(t_map *map)
{
	if (!map->x || !map->y || !map->z)
		return (0);
	return (1);
}

t_map		*read_map(t_lines *start, t_window *window)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->x_max = 0;
	map->y_max = 0;
	map->x_min = 0;
	map->y_min = 0;
	map->y = find_y(start);
	if (map->y < 1)
		return (NULL);
	map->x = find_x(start);
	if (map->x < 1)
		return (NULL);
	if (map->x == 1 && map->y == 1)
		one_pixel(window);
	find_z(start, map);
	if (!check_errors(map))
	{
		del_lines(start);
		del_map(map);
		return (NULL);
	}
	return (map);
}
