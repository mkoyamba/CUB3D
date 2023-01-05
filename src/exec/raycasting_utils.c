/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:02:41 by mkoyamba          #+#    #+#             */
/*   Updated: 2023/01/05 13:08:57 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

float	return_check_se(t_map *map, float raydir, float *x, float *y)
{
	if (((map->ray_len_v < map->ray_len_h)
			|| map->ray_len_h == -1) && map->ray_len_v != -1)
	{
		*y = map->player.y + map->ray_len_v * sin((raydir - 1) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (map->ray_len_v);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = NORTH;
		return (map->ray_len_h);
	}
}

float	return_check_sw(t_map *map, float raydir, float *x, float *y)
{
	if (((map->ray_len_v < map->ray_len_h)
			|| map->ray_len_h == -1) && map->ray_len_v != -1)
	{
		*y = map->player.y + map->ray_len_v * cos((raydir - 2) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = EAST;
		return (map->ray_len_v);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = NORTH;
		return (map->ray_len_h);
	}
}

float	return_check_ne(t_map *map, float raydir, float *x, float *y)
{
	if (((map->ray_len_v < map->ray_len_h)
			|| map->ray_len_h == -1) && map->ray_len_v != -1)
	{
		*y = map->player.y - map->ray_len_v * cos((raydir) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (map->ray_len_v);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = SOUTH;
		return (map->ray_len_h);
	}
}

float	return_check_nw(t_map *map, float raydir, float *x, float *y)
{
	if (((map->ray_len_v < map->ray_len_h)
			|| map->ray_len_h == -1) && map->ray_len_v != -1)
	{
		*y = map->player.y - map->ray_len_v * sin((raydir - 3) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = EAST;
		return (map->ray_len_v);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = SOUTH;
		return (map->ray_len_h);
	}
}

void	raycast_draw_wall(int n, int i, t_map *map, int middle_part)
{
	while (i < SCREEN_HEIGHT / 2 - middle_part / 2)
	{
		put_pixel(n, i, map->ceiling, map);
		i++;
	}
	map->column.start = i;
	while (i < SCREEN_HEIGHT / 2 + middle_part / 2)
	{
		set_wall_color(map, n, i);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		put_pixel(n, i, map->floor, map);
		i++;
	}
}
