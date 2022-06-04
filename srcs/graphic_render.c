/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:59:15 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:33:12 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

int	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return (0);
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
	return (1);
}

double	ft_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_abs(double a)
{
	if (a < 0)
		return (a *= -1);
	return (a);
}

int	bresenham_algo(t_data *data, t_point begin, t_point end, t_point origin)
{
	double	x_step;
	double	y_step;
	double	color_step;
	double	max;

	x_step = end.x - begin.x;
	y_step = end.y - begin.y;
	color_step = end.color - begin.color;
	max = ft_max(ft_abs(x_step), ft_abs(y_step));
	x_step /= max;
	y_step /= max;
	color_step /= max;
	while ((int)(begin.x - end.x) || (int)(begin.y - end.y))
	{
		if (!img_pix_put(&data->img, origin.x + begin.x, origin.y + begin.y,
				begin.color))
			return (1);
		begin.x += x_step;
		begin.y += y_step;
		begin.color += color_step;
	}
	return (0);
}

int	render(t_data *data)
{
	int		x;
	int		y;
	t_point	origin;

	origin.x = WIN_WIDTH / 2;
	origin.y = WIN_HEIGHT / 2;
	y = -1;
	if (!data->win_ptr)
		return (1);
	while (++y < data->height_map)
	{
		x = -1;
		while (++x < data->width_map)
		{
			if (x != data->width_map - 1)
				bresenham_algo(data, data->map[y][x], data->map[y][x + 1],
					origin);
			if (y != 0)
				bresenham_algo(data, data->map[y][x], data->map[y - 1][x],
					origin);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	return (0);
}
