/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:20:57 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_point	**map;
	int		width_map;
	int		height_map;
	int		y;

	y = 0;
	if (ac != 2)
		return (EXIT_FAILURE);
	map = parse_fdf(av[1], &width_map, &height_map);
	graphic_process(map, width_map, height_map);
	while (y < height_map)
		free(map[y++]);
	free(map);
	return (0);
}
