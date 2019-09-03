/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dimention.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:55:49 by samymone          #+#    #+#             */
/*   Updated: 2019/09/03 13:09:04 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			find_y(t_lines *start)
{
	int		y;
	t_lines	*temp;

	if (start->line == NULL)
		return (0);
	temp = start;
	y = 0;
	while (temp)
	{
		y++;
		temp = temp->next;
	}
	return (y);
}

int			find_x(t_lines *start)
{
	int		x_xm[2];
	t_lines	*temp;
	char	**split;

	x_xm[1] = 0;
	temp = start;
	while (temp != NULL/*->next*/)
	{
		x_xm[0] = 0;
		split = ft_strsplit(temp->line, ' ');
		while (split[x_xm[0]])
		{
			if (check_split(split[x_xm[0]]) == -1)
				return (freeshing_x(split, x_xm[0]));
			free(split[x_xm[0]++]);
		}
		free(split);
		x_xm[1] ? x_xm[1] : (x_xm[1] = x_xm[0]);
		if (x_xm[0] != x_xm[1])
			return (0);
		temp = temp->next;
	}
	return (x_xm[0]);
}

int			map_allocation(t_map *map)
{
	if (!(map->z = (int**)malloc(sizeof(int*) * (map->y + 1))))
		return (-1);
	if (!(map->color = (unsigned int**)malloc(sizeof(unsigned int**)
			* (map->y + 1))))
		return (-1);
	return (1);
}

void		z_filling(t_map *map, int i, int yy, char **split)
{
	if (ft_strchr(split[i], ','))
	{
		map->z[yy][i] = ft_atoi(split[i]);
		map->color[yy][i] = ft_atoi_base(ft_strchr(split[i], ','));
	}
	else
	{
		map->z[yy][i] = ft_atoi(split[i]);
		map->color[yy][i] = 0;
	}
	free(split[i]);
}

void		find_z(t_lines *start, t_map *map)
{
	int		yy;
	int		i;
	char	**split;
	t_lines	*temp;

	temp = start;
	yy = 0;
	if (map_allocation(map) == -1)
		return ;
	while (yy < map->y)
	{
		i = 0;
		split = ft_strsplit(temp->line, ' ');
		map->z[yy] = (int*)malloc(sizeof(int) * map->x);
		map->color[yy] = (unsigned int*)malloc(sizeof(unsigned int*) * map->x);
		while (i < map->x)
		{
			z_filling(map, i, yy, split);
			i++;
		}
		free(split);
		yy++;
		temp = temp->next;
	}
}
