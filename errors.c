/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:52:50 by cyuriko           #+#    #+#             */
/*   Updated: 2019/08/29 19:21:34 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	one_pixel(t_window *window)
{
	char	*str;
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 200, 200, "my my, a pixel");
	str = "u want a pixel";
	mlx_string_put(mlx_ptr, win_ptr, 10, 100, 0xFFFFFF, str);
	str = "here's a pixel";
	mlx_string_put(mlx_ptr, win_ptr, 10, 150, 0xFFFFFF, str);
	mlx_pixel_put(mlx_ptr, win_ptr, 100, 50, 0xFFFFFF);
	mlx_hook(win_ptr, 17, 1L << 17, close_window, window);
	mlx_hook(win_ptr, 2, 1L << 0, key_press, window);
	mlx_loop(mlx_ptr);
}

void	print_error(int error, t_window *window)
{
	del_win(window);
	if (error == 1)
		write(2, "failed to create window", 23);
	else if (error == 2)
		write(2, "empty or invalid file", 21);
	else if (error == 3)
		write(2, "failed to read from fd", 22);
	else if (error == 4)
		write(2, "incorrect input", 15);
	else if (error == 5)
		write(2, "failed to create map", 20);
	exit(0);
}

int		check_split(char *split)
{
	int ijg[3];

	ijg[0] = 0;
	while (ft_isdigit(split[ijg[0]]))
		ijg[0]++;
	if (split[ijg[0]] == '\0')
		return (1);
	if (split[ijg[0]++] == ',' && !(ijg[1] = 0))
	{
		if (split[ijg[0]] && split[ijg[0]] == '0' && split[ijg[0] + 1] &&
		(split[ijg[0] + 1] == 'x' || split[ijg[0] + 1] == 'X'))
			ijg[0] += 2;
		ijg[2] = ijg[0];
		while (split[ijg[0]])
		{
			if ((split[ijg[0]] >= 'a' && split[ijg[0]] <= 'f') ||
			(split[ijg[0]] >= 'A' && split[ijg[0]] <= 'F') ||
			ft_isdigit(split[ijg[0]]))
				ijg[1]++;
			ijg[0]++;
		}
	}
	if ((ijg[1] == 6 || ijg[1] == 8) && (ijg[0] - ijg[2] == ijg[1]))
		return (1);
	return (-1);
}
