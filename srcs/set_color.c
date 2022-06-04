/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:36:44 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_color(t_point **map, int max_z, int min_z, t_data *data)
{
	double	color_step;
	int		color_down;
	int		color_up;
	int		y;
	int		x;

	y = 0;
	color_up = 0xFF0000;
	color_down = 0xFFFFFF;
	color_step = 0;
	if (max_z - min_z)
		color_step = (color_up - color_down) / (max_z - min_z);
	while (y < data->height_map)
	{
		x = 0;
		while (x < data->width_map)
		{
			(map[y] + x)->color = color_down + ((map[y] + x)->z - min_z)
				* color_step;
			x++;
		}
		y++;
	}
}

int	set_color(t_point **map, t_data *data)
{
	int	max_z;
	int	min_z;
	int	y;
	int	x;

	y = 0;
	max_z = (map[y] + y)->z;
	min_z = (map[y] + y)->z;
	while (y < data->height_map)
	{
		x = 0;
		while (x < data->width_map)
		{
			if ((map[y] + x)->z < min_z)
				min_z = (map[y] + x)->z;
			else if ((map[y] + x)->z > max_z)
				max_z = (map[y] + x)->z;
			x++;
		}
		y++;
	}
	put_color(map, max_z, min_z, data);
	return (max_z - min_z);
}
