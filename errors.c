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

void	one_pixel(void)
{
	char *str;
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 200, 200, "my my, a pixel");
	str = "u want a pixel here's a pixel";
	mlx_pixel_put(mlx_ptr, win_ptr, 100, 50, 0xFFFFFF);
	mlx_string_put(mlx_ptr, win_ptr, 10, 100, 0xFFFFFF, str);
}

int		print_error(int error)
{
	if (error == 1)
		write(2, "failed to create window", 24);
	return (-1);
}