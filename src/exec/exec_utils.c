/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:30:08 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/07 19:43:01 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

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

int	is_valid_pos(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '0')
		return (0);
	return (1);
}

float	modulo_perso(float result, float modulo)
{
	if (result < 0)
		result = modulo + result;
	if (result >= modulo)
		result = result - modulo;
	return (result);
}
