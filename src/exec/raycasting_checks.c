/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:53:38 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/08 12:02:33 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	check_map_ray(float x, float y, float *raylen_HV, t_map *map)
{
	if (!is_in_map(x, y, map))
	{
		*raylen_HV = -1;
		return (1);
	}
	if (!is_valid_pos(map, x, y))
	{
		*raylen_HV =
			sqrtf(powf(x - map->player.x, 2) + powf(y - map->player.y, 2));
		return (2);
	}
	return (0);
}

float	ray_split_se(t_map *map, float raydir, float *x, float *y)
{
	float ray_len_V;
	float ray_len_H;

	*x = (int)map->player.x + 1;
	*y = map->player.y + ((*x - map->player.x) * tan((raydir - 1) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x + 0.000001, *y, &ray_len_V, map))
			break ;
		*x += 1;
		*y += tan((raydir - 1) * M_PI_2);
	}
	*y = (int)map->player.y + 1;
	*x = map->player.x + ((*y - map->player.y) / tan((raydir - 1) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y + 0.000001, &ray_len_H, map))
			break ;
		*x += 1 / tan((raydir - 1) * M_PI_2);
		*y += 1;
	}
	if (((ray_len_V < ray_len_H) || ray_len_H == -1) && ray_len_V != -1)
	{
		*y = map->player.y + ray_len_V * sin((raydir - 1) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (ray_len_V);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = NORTH;
		return (ray_len_H);
	}
}

float	ray_split_sw(t_map *map, float raydir, float *x, float *y)
{
	float ray_len_V;
	float ray_len_H;

	*x = (int)map->player.x;
	*y = map->player.y + ((map->player.x - *x) / tan((raydir - 2) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x - 0.000001, *y, &ray_len_V, map))
			break ;
		*x -= 1;
		*y += 1 / tan((raydir - 2) * M_PI_2);
	}
	*y = (int)map->player.y + 1;
	*x = map->player.x - ((*y - map->player.y) * tan((raydir - 2) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y + 0.000001, &ray_len_H, map))
			break ;
		*x -= tan((raydir - 2) * M_PI_2);
		*y += 1;
	}
	if (((ray_len_V < ray_len_H) || ray_len_H == -1) && ray_len_V != -1)
	{
		*y = map->player.y + ray_len_V * cos((raydir - 2) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = EAST;
		return (ray_len_V);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = NORTH;
		return (ray_len_H);
	}
}

float	ray_split_ne(t_map *map, float raydir, float *x, float *y)
{
	float ray_len_V;
	float ray_len_H;

	*x = (int)map->player.x + 1;
	*y = map->player.y - ((*x - map->player.x) / tan((raydir) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x + 0.000001, *y, &ray_len_V, map))
			break ;
		*x += 1;
		*y -= 1 / tan((raydir) * M_PI_2);
	}
	*y = (int)map->player.y;
	*x = map->player.x + ((map->player.y - *y) * tan((raydir) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y - 0.000001, &ray_len_H, map))
			break ;
		*x += tan((raydir) * M_PI_2);
		*y -= 1;
	}
	if (((ray_len_V < ray_len_H) || ray_len_H == -1) && ray_len_V != -1)
	{
		*y = map->player.y - ray_len_V * cos((raydir) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = WEST;
		return (ray_len_V);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = SOUTH;
		return (ray_len_H);
	}
}

float	ray_split_nw(t_map *map, float raydir, float *x, float *y)
{
	float ray_len_V;
	float ray_len_H;

	*x = (int)map->player.x;
	*y = map->player.y - ((map->player.x - *x) * tan((raydir - 3) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x - 0.000001, *y, &ray_len_V, map))
			break ;
		*x -= 1;
		*y -= tan((raydir - 3) * M_PI_2);
	}
	*y = (int)map->player.y;
	*x = map->player.x - ((map->player.y - *y) / tan((raydir - 3) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y - 0.000001, &ray_len_H, map))
			break ;
		*y -= 1;
		*x -= 1 / tan((raydir - 3) * M_PI_2);
	}
	if (((ray_len_V < ray_len_H) || ray_len_H == -1) && ray_len_V != -1)
	{
		*y = map->player.y - ray_len_V * sin((raydir - 3) * M_PI_2);
		map->wall_pos = *y - (int)*y;
		map->wall_color = EAST;
		return (ray_len_V);
	}
	else
	{
		map->wall_pos = *x - (int)*x;
		map->wall_color = SOUTH;
		return (ray_len_H);
	}
}
