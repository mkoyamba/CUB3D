/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:16:39 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 17:34:53 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	put_pixel(int x, int y, int color, t_map *map)
{
	int				pixel;
	unsigned char	*color_buf;
	int				iter;

	iter = 0;
	while (iter < 2)
	{
		pixel = (y * map->line_bytes) + ((x + iter) * 4);
		color_buf = (unsigned char *)&color;
		map->buffer[pixel] = color_buf[3];
		map->buffer[pixel + 1] = color_buf[2];
		map->buffer[pixel + 2] = color_buf[1];
		map->buffer[pixel + 3] = (unsigned char)0;
		iter++;
	}
}

float	return_check_se(t_map *map, float raydir, float *x, float *y)
{
	if (((map->ray_len_v < map->ray_len_h)
			|| map->ray_len_h == -1) && map->ray_len_v != -1)
	{
		map->column.type = map->column.typev;
		*y = map->player.y + map->ray_len_v * sin((raydir - 1) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (map->ray_len_v);
	}
	else
	{
		map->column.type = map->column.typeh;
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
		map->column.type = map->column.typev;
		*y = map->player.y + map->ray_len_v * cos((raydir - 2) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = EAST;
		return (map->ray_len_v);
	}
	else
	{
		map->column.type = map->column.typeh;
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
		map->column.type = map->column.typev;
		*y = map->player.y - map->ray_len_v * cos((raydir) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (map->ray_len_v);
	}
	else
	{
		map->column.type = map->column.typeh;
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
		map->column.type = map->column.typev;
		return (map->ray_len_v);
	}
	else
	{
		map->column.type = map->column.typeh;
		map->wall_pos = *x - (int)*x;
		map->wall_color = SOUTH;
		return (map->ray_len_h);
	}
}
