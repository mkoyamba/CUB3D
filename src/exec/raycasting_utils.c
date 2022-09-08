/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:40:07 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 18:35:45 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static int	compare_ray_colision(
				float beforex, float beforey, float new_pos_x, float new_pos_y)
{
	int	casex;
	int	casey;

	casex = 0;
	casey = 0;
	if ((int)beforex != (int)new_pos_x)
		casex = 1;
	else if ((int)beforey != (int)new_pos_y)
		casey = 1;
	if (casex && !casey)
		return (1);
	else if (!casex && casey)
		return (2);
	else
		return (3);
	return (0);
}

static int	set_before(float raydir, float new_pos_x, float new_pos_y)
{
	float	beforex;
	float	beforey;

	if (raydir > 0 && raydir < 1)
	{
		beforex = new_pos_x - 0.01 * sin(raydir * M_PI_2);
		beforey = new_pos_y + 0.01 * cos(raydir * M_PI_2);
	}
	else if (raydir > 1 && raydir < 2)
	{
		beforex = new_pos_x - 0.01 * cos((raydir - 1) * M_PI_2);
		beforey = new_pos_y - 0.01 * sin((raydir - 1) * M_PI_2);
	}
	else if (raydir > 2 && raydir < 3)
	{
		beforex = new_pos_x + 0.01 * sin((raydir - 2) * M_PI_2);
		beforey = new_pos_y - 0.01 * cos((raydir - 2) * M_PI_2);
	}
	else
	{
		beforex = new_pos_x + 0.01 * cos((raydir - 3) * M_PI_2);
		beforey = new_pos_y + 0.01 * sin((raydir - 3) * M_PI_2);
	}
	return (compare_ray_colision(beforex, beforey, new_pos_x, new_pos_y));
}

static void	change_wall_color(int c_case, float raydir, t_map *map)
{
	if (c_case == 1)
	{
		if (raydir < 2)
			map->wall_color = WALL_WEST;
		else
			map->wall_color = WALL_EAST;
	}
	else if (c_case == 2)
	{
		if ((raydir > 0 && raydir < 1) || ((raydir > 3 && raydir < 4)))
			map->wall_color = WALL_SOUTH;
		else
			map->wall_color = WALL_NORTH;
	}
}

static void		get_wall_color_next(
			t_map *map, float raydir, float *new_pos_x, float *new_pos_y)
{
	while (raydir > 2 && raydir < 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * sin((raydir - 2) * M_PI_2);
		*new_pos_y += 0.01 * cos((raydir - 2) * M_PI_2);
	}
	while (raydir > 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * cos((raydir - 3) * M_PI_2);
		*new_pos_y -= 0.01 * sin((raydir - 3) * M_PI_2);
	}
}

void	get_wall_color(t_map *map, float raydir)
{
	float	new_pos_x;
	float	new_pos_y;
	int		c_case;

	new_pos_x = map->player.x;
	new_pos_y = map->player.y;
	while (raydir > 0 && raydir < 1 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * sin(raydir * M_PI_2);
		new_pos_y -= 0.01 * cos(raydir * M_PI_2);
	}
	while (raydir > 1 && raydir < 2 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * cos((raydir - 1) * M_PI_2);
		new_pos_y += 0.01 * sin((raydir - 1) * M_PI_2);
	}
	get_wall_color_next(map, raydir, &new_pos_x, &new_pos_y);
	c_case = set_before(raydir, new_pos_x, new_pos_y);
	change_wall_color(c_case, raydir, map);
}