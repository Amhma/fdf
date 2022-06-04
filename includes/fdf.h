/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:10:20 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:38:20 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define WIN_HEIGHT 2000
# define WIN_WIDTH 3600

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_point
{
	double	y;
	double	x;
	int		z;
	int		color;
}			t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_point	**map;
	int		width_map;
	int		height_map;
	int		range_z;
}			t_data;

//		error.c
void	error_mlx_data(t_point **map, int height_map, void *to_free_1,
			void *to_free_2);
void	error_malloc_strs(char **map);
void	error_malloc_strs2(t_point **map_int, char **map, int j);

//		parse_fdf.c
t_point	**parse_fdf(char *arg, int *width_map, int *height_map);

//		fdf.c
int		set_color(t_point **map, t_data *data);

//		graphics_process.c
int		graphic_process(t_point **map, int width_map, int height_map);

//		graphic_render.c
int		render(t_data *data);

//		graphic_hook.c
void	handle_hooks(t_data *data);

#endif
