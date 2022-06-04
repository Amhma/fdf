/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:03:03 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:19:42 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	error_mlx_data(t_point **map, int height_map, void *to_free_1,
	void *to_free_2)
{
	int	y;

	y = 0;
	if (to_free_1)
		free(to_free_1);
	if (to_free_2)
		free(to_free_2);
	while (y < height_map)
		free(map[y++]);
	free(map);
	ft_putendl_fd("data initialize error", 2);
	exit(EXIT_FAILURE);
}

void	error_malloc_strs(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		free(map[y++]);
	free(map);
	ft_putendl_fd("error malloc strs", 2);
	exit(EXIT_FAILURE);
}

void	error_malloc_strs2(t_point **map_int, char **map, int j)
{
	int	y;

	y = 0;
	while (map[y])
		free(map[y++]);
	free(map);
	y = 0;
	while (y < j)
		free(map_int[y++]);
	free(map_int);
	ft_putendl_fd("error malloc strs (2)", 2);
	exit(EXIT_FAILURE);
}
