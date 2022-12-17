/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:31:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/17 19:00:52 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

static int	check_is_sprite(float x, float y, t_map *map)
{
	if (!is_in_map(x, y, map))
		return (-1);
	if (map->map[(int)y][(int)x] == '4')
		return (1);
	return (0);
}

static int	check_near(float raydir, t_sprite *sprite, int mode, t_map *map)
{
	if (mode == HORIZONTAL && raydir >= 0 && raydir < M_PI)
		return (check_is_sprite(sprite->Hx, sprite->Hy - 0.000001, map));
	else if (mode == HORIZONTAL)
		return (check_is_sprite(sprite->Hx, sprite->Hy + 0.000001, map));
	else if (mode == VERTICAL && raydir >= M_PI_2 && raydir < 3 * M_PI_2)
		return (check_is_sprite(sprite->Vx - 0.000001, sprite->Vy, map));
	else if (mode == VERTICAL)
		return (check_is_sprite(sprite->Vx + 0.000001, sprite->Vy, map));
	return (-1);
}

int	new_sprite_pos(float raydir, t_sprite *sprite, int mode, t_map *map)
{
	if (mode == HORIZONTAL && raydir >= 0 && raydir < M_PI)
	{
		sprite->Hx += 1 / tan(raydir);
		sprite->Hy -= 1;
	}
	else if (mode == HORIZONTAL)
	{
		sprite->Hx -= 1 / tan(raydir);
		sprite->Hy += 1;
	}
	else if (mode == VERTICAL && raydir >= M_PI_2 && raydir < 3 * M_PI_2)
	{
		sprite->Vx -= 1;
		sprite->Vy += tan(raydir);
	}
	else if (mode == VERTICAL)
	{
		sprite->Vx += 1;
		sprite->Vy -= tan(raydir);
	}
	return(check_near(raydir, sprite, mode, map));
}
