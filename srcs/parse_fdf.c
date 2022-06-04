/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:25:50 by amahla            #+#    #+#             */
/*   Updated: 2022/06/04 21:59:34 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_point(t_point **map, int y, int x, char *nb)
{
	int	i;

	i = 0;
	(map[y] + x)->y = (double)y;
	(map[y] + x)->x = (double)x;
	(map[y] + x++)->z = ft_atoi(nb);
	while (*(nb + i) && *(nb + i) != ' ')
		i++;
	return (i);
}

void	strs_len(char **strs, int *height_map, int *width_map)
{
	int	i;
	int	j;
	int	y;

	y = 0;
	i = 0;
	j = 0;
	while (*(strs[y] + i))
	{
		if (ft_isdigit(*(strs[y] + i)))
		{
			j++;
			while (*(strs[y] + i) && *(strs[y] + i) != ' ')
				i++;
		}
		else
			i++;
	}
	while (strs[y])
		y++;
	*height_map = y;
	*width_map = j;
}	

char	*read_fdf(char *arg)
{
	int		fd;
	char	*line;
	char	*map_uni;

	map_uni = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
	{
		perror("open ");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		map_uni = ft_strjoin2(map_uni, line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (map_uni);
}

t_point	**parse_int(char **map, int height_map, int width_map)
{
	t_point	**map_point;
	int		i;
	int		x;
	int		y;

	y = -1;
	map_point = malloc(height_map * sizeof(t_point *));
	if (!map_point)
		error_malloc_strs(map);
	while (++y < height_map)
	{
		x = 0;
		i = 0;
		map_point[y] = malloc((width_map) * sizeof(t_point));
		if (!map_point[y])
			error_malloc_strs2(map_point, map, y);
		while (x < width_map && *(map[y] + i))
		{
			while (!ft_isdigit(*(map[y] + i)) && *(map[y] + i) != '-')
				i++;
			i += set_point(map_point, y, x++, map[y] + i);
		}
	}
	return (map_point);
}

t_point	**parse_fdf(char *arg, int *width_map, int *height_map)
{
	char	*temp;
	char	**map;
	t_point	**map_point;
	int		y;

	y = 0;
	temp = read_fdf(arg);
	if (!temp)
	{
		ft_putendl_fd("file error : corrupted file", 2);
		exit(EXIT_FAILURE);
	}
	map = ft_split(temp, '\n');
	free(temp);
	if (!map)
		exit(EXIT_FAILURE);
	strs_len(map, height_map, width_map);
	map_point = parse_int(map, *height_map, *width_map);
	while (map[y])
		free(map[y++]);
	free(map);
	return (map_point);
}
