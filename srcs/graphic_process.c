/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:31:14 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

int	auto_zoom(t_data *data)
{
	int	zoom;

	zoom = 1;
	while (zoom * data->width_map < WIN_WIDTH * 2 / 5
		&& zoom * data->height_map < WIN_WIDTH * 2 / 5)
		zoom++;
	return (zoom);
}

int	auto_zoom_z(t_data *data, int y, int x, int zoom)
{
	if (data->range_z <= 10)
		data->map[y][x].z *= (zoom / 2);
	else if (data->range_z <= 30)
		data->map[y][x].z *= (zoom / 6);
	return (zoom);
}

void	isometric_transfomation(t_data *data)
{
	int		y;
	int		x;
	int		temp;
	int		zoom;

	y = -1;
	zoom = auto_zoom(data);
	while (++y < data->height_map)
	{
		x = 0;
		while (x < data->width_map)
		{
			auto_zoom_z(data, y, x, zoom);
			data->map[y][x].x = (data->map[y][x].x - data->width_map / 2)
				* zoom;
			data->map[y][x].y = (data->map[y][x].y - data->height_map / 2)
				* zoom;
			temp = data->map[y][x].x;
			data->map[y][x].x = ((data->map[y][x].x - data->map[y][x].y)
					* cos(0.523599));
			data->map[y][x].y = ((temp + data->map[y][x].y)
					* sin(0.523599) - data->map[y][x].z);
			x++;
		}
	}
}

int	graphic_process(t_point **map, int width_map, int height_map)
{
	t_data	data;

	data.height_map = height_map;
	data.width_map = width_map;
	data.map = map;
	data.range_z = set_color(map, &data);
	isometric_transfomation(&data);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		error_mlx_data(map, data.height_map, NULL, NULL);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!data.win_ptr)
		error_mlx_data(map, 0, data.mlx_ptr, NULL);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	handle_hooks(&data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
