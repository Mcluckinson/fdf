/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_works.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:24:17 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/14 19:40:12 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_window	*set_up_window(int win_width, int win_height)
{
	t_window	*window;

	window = (t_window*)malloc(sizeof(window));
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, win_width + 200, win_height + 200, "FDF");
	window->img_ptr = mlx_new_image(window->mlx_ptr, win_width, win_height);
	window->linesize = (int*)malloc(sizeof(int));
	*window->linesize = win_width * UNIQ_BPP;
	window->depth = (int*)malloc(sizeof(int));
	*window->depth = UNIQ_BPP * 8;
	window->endian = (int*)malloc(sizeof(int));
	*window->endian = 0;
	window->img_data = mlx_get_data_addr(window->img_ptr, window->depth, window->linesize, window->endian);
	return (window);
}

/*int	main()
{

	*endian = 0;

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	printf ("ok!\n");
	return (0);
}

*/