/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:30:08 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 18:38:06 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	refresh_screen(t_map *map)
{
	int		n;
	float	raydir;

	n = 0;
	while (n < SCREEN_WIDTH)
	{
		raydir = modulo_perso(map->player.dir
				+ (n - SCREEN_WIDTH / 2) * 0.5 / SCREEN_WIDTH, 4);
		raycast(n, map, raydir);
		n += 2;
	}
	if (!map->minimap)
	{
		put_minimap(map);
		put_crosshair(map);
	}
	else
		put_big_minimap(map);
	put_coin_img(map);
	if (map->got_coin > 0)
		put_coin_obtained(map);
}

float	new_colision_x(t_map *map)
{
	float	move_dir;

	move_dir = get_move_dir(map);
	if (move_dir >= NORTH && move_dir < EAST)
		return (sin(move_dir * M_PI_2) * COLLISION_LEN);
	else if (move_dir >= EAST && move_dir < SOUTH)
		return (cos((move_dir - 1) * M_PI_2) * COLLISION_LEN);
	else if (move_dir >= SOUTH && move_dir < WEST)
		return (-sin((move_dir - 2) * M_PI_2) * COLLISION_LEN);
	else
		return (-cos((move_dir - 3) * M_PI_2) * COLLISION_LEN);
}

float	new_colision_y(t_map *map)
{
	float	move_dir;

	move_dir = get_move_dir(map);
	if (move_dir >= NORTH && move_dir < EAST)
		return (-cos(move_dir * M_PI_2) * COLLISION_LEN);
	else if (move_dir >= EAST && move_dir < SOUTH)
		return (sin((move_dir - 1) * M_PI_2) * COLLISION_LEN);
	else if (move_dir >= SOUTH && move_dir < WEST)
		return (cos((move_dir - 2) * M_PI_2) * COLLISION_LEN);
	else
		return (-sin((move_dir - 3) * M_PI_2) * COLLISION_LEN);
}

float	modulo_perso(float result, float modulo)
{
	if (result < 0)
		result = modulo + result;
	if (result >= modulo)
		result = result - modulo;
	return (result);
}

void	manahge_door(t_map *map)
{
	float	dir;

	dir = ft_map_values_f(map->player.dir, 4, 1);
	map->player.open = 0;
	raycast(SCREEN_WIDTH / 2, map, map->player.dir);
	if ((map->column.type == '3' || map->column.type == '2')
		&& map->column.raylen < 2.5)
	{
		manahge_door_utils(map, dir);
		refresh_screen(map);
		mlx_put_image_to_window(
			map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	}
}
