/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dimention.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samymone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 22:55:49 by samymone          #+#    #+#             */
/*   Updated: 2019/08/30 22:58:22 by samymone         ###   ########.fr       */
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
	while (temp->next)
	{
		y++;
		temp = temp->next;
	}
	return (y);
}

int 	find_x(t_lines *start)
{
	int		x;
	int		x_max;
	t_lines	*temp;
	char	**split;

	x = 0;
	x_max = 0;
	temp = start;
	while (temp->next)
	{
		x = 0;
		split = ft_strsplit(temp->line, ' ');
		while (split[x])
		{
			if (check_split(split[x]) == -1)
			{
				free(split[x]);
				free(split);
				return (-1);
			}
			free(split[x]);
			x++;
		}
		free(split);
		if (!x_max)
			x_max = x;
		else if (x != x_max)
			return (0);
		temp = temp->next;
	}
	return (x);
}

void	find_z(t_lines *start, t_map *map)
{
	int		yy;
	int		i;
	char	**split;
	t_lines	*temp;

	temp = start;
	yy = 0;
	if (!(map->z = (int**)malloc(sizeof(int*) * (map->y + 1))))
		return ;
	if (!(map->color = (unsigned int**)malloc(sizeof(unsigned int**)
											  * (map->y + 1))))
		return ;
	while (yy < map->y)
	{
		i = 0;
		split = ft_strsplit(temp->line, ' ');
		map->z[yy] = (int*)malloc(sizeof(int) * map->x);
		map->color[yy] = (unsigned int*)malloc(sizeof(unsigned int*) * map->x);
		while (i < map->x)
		{
			if (strchr(split[i], ','))
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
			i++;
		}
		free(split);
		yy++;
		temp = temp->next;
	}
}
