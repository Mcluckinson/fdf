/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attune_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyuriko <cyuriko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:14:53 by cyuriko           #+#    #+#             */
/*   Updated: 2019/07/15 14:17:12 by cyuriko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	*fix_orig(t_coords *start)
{
	t_coords	*result;

	result = start;
	while (start->next != NULL)
	{
		start->x0 = start->x0 * 10;
		start->x1 = start->x1 * 10;
		start->y0 = start->y0 * 10;
		start->y1 = start->y1 * 10;
		start->z0 = start->z0 * 10;
		start->z1 = start->z1 * 10;
		start = start->next;
	}
	start->x0 = start->x0 * 10;
	start->x1 = start->x1 * 10;
	start->y0 = start->y0 * 10;
	start->y1 = start->y1 * 10;
	start->z0 = start->z0 * 10;
	start->z1 = start->z1 * 10;
	return (result);
}

t_coords	*iso(t_coords *start)
{
	t_coords *turned;
//	t_coords *result;

	turned = NULL;
//	result = turned;
	while (start->next != NULL)
	{
		turned = new_coords(turned);
		turned->x0 = (start->x0 - start->y0)  * cos(0.523599);
		turned->x1 = (start->x1 - start->y1)  * cos(0.523599);
		turned->y0 = (start->z0) * -1 + ((start->x0 + start->y0)  * sin(0.523599));
		turned->y1 = (start->z1) * -1 + ((start->x1 + start->y1)  * sin(0.523599));
		turned->z0 = start->z0;
		turned->z1 = start->z1;
		start = start->next;
	}
	turned = new_coords(turned);
	turned->x0 = (start->x0 - start->y0)  * cos(0.523599);
	turned->x1 = (start->x1 - start->y1)  * cos(0.523599);
	turned->y0 = (start->z0) * -1 + ((start->x0 + start->y0)  * sin(0.523599));
	turned->y1 = (start->z1) * -1 + ((start->x1 + start->y1)  * sin(0.523599));
	turned->z0 = start->z0;
	turned->z1 = start->z1;
	return (turned);
}
/*Slanting right:

new_x = (x + y) * cos(angle);
new_y = (x - y) * sin(angle) - z;
Slanting left:

new_x = (x - y) * -cos(angle);
new_y = ((x + y) * sin(angle)) - z;
Mirror image slanting right:

new_x = (x - y) * cos(angle);
new_y = ((x + y) * sin(angle)) - z;
Mirror image slanting left:

new_x = (x + y) * -cos(angle);
new_y = ((x - y) * sin(angle)) - z;
*/
/*static void iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}*/