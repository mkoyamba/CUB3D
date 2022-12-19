/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:53:38 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 15:32:57 by mkoyamba         ###   ########.fr       */
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
		*raylen_HV = sqrtf(
				powf(x - map->player.x, 2) + powf(y - map->player.y, 2));
		return (2);
	}
	return (0);
}

float	ray_split_se(t_map *map, float raydir, float *x, float *y)
{
	*x = (int)map->player.x + 1;
	*y = map->player.y + ((*x - map->player.x) * tan((raydir - 1) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x + 0.000001, *y, &(map->ray_len_v), map))
			break ;
		*x += 1;
		*y += tan((raydir - 1) * M_PI_2);
	}
	*y = (int)map->player.y + 1;
	*x = map->player.x + ((*y - map->player.y) / tan((raydir - 1) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y + 0.000001, &(map->ray_len_h), map))
			break ;
		*x += 1 / tan((raydir - 1) * M_PI_2);
		*y += 1;
	}
	return (return_check_se(map, raydir, x, y));
}

float	ray_split_sw(t_map *map, float raydir, float *x, float *y)
{
	*x = (int)map->player.x;
	*y = map->player.y + ((map->player.x - *x) / tan((raydir - 2) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x - 0.000001, *y, &(map->ray_len_v), map))
			break ;
		*x -= 1;
		*y += 1 / tan((raydir - 2) * M_PI_2);
	}
	*y = (int)map->player.y + 1;
	*x = map->player.x - ((*y - map->player.y) * tan((raydir - 2) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y + 0.000001, &(map->ray_len_h), map))
			break ;
		*x -= tan((raydir - 2) * M_PI_2);
		*y += 1;
	}
	return (return_check_sw(map, raydir, x, y));
}

float	ray_split_ne(t_map *map, float raydir, float *x, float *y)
{
	*x = (int)map->player.x + 1;
	*y = map->player.y - ((*x - map->player.x) / tan((raydir) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x + 0.000001, *y, &(map->ray_len_v), map))
			break ;
		*x += 1;
		*y -= 1 / tan((raydir) * M_PI_2);
	}
	*y = (int)map->player.y;
	*x = map->player.x + ((map->player.y - *y) * tan((raydir) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y - 0.000001, &(map->ray_len_h), map))
			break ;
		*x += tan((raydir) * M_PI_2);
		*y -= 1;
	}
	return (return_check_ne(map, raydir, x, y));
}

float	ray_split_nw(t_map *map, float raydir, float *x, float *y)
{
	*x = (int)map->player.x;
	*y = map->player.y - ((map->player.x - *x) * tan((raydir - 3) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x - 0.000001, *y, &(map->ray_len_v), map))
			break ;
		*x -= 1;
		*y -= tan((raydir - 3) * M_PI_2);
	}
	*y = (int)map->player.y;
	*x = map->player.x - ((map->player.y - *y) / tan((raydir - 3) * M_PI_2));
	while (1)
	{
		if (check_map_ray(*x, *y - 0.000001, &(map->ray_len_h), map))
			break ;
		*y -= 1;
		*x -= 1 / tan((raydir - 3) * M_PI_2);
	}
	return (return_check_nw(map, raydir, x, y));
}
