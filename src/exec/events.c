/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:30:02 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 16:21:02 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

float	get_move_dir(t_map *map)
{
	float	axe;
	float	side;
	float	move_dir;

	axe = map->player.forward - map->player.backward;
	side = map->player.right - map->player.left;
	if (axe == 1 && side == 1)
		move_dir = modulo_perso(map->player.dir + 0.5, 4);
	else if (axe == 1 && side == -1)
		move_dir = modulo_perso(map->player.dir - 0.5, 4);
	else if (axe == -1 && side == 1)
		move_dir = modulo_perso(map->player.dir + 1.5, 4);
	else if (axe == -1 && side == -1)
		move_dir = modulo_perso(map->player.dir - 1.5, 4);
	else if (axe == -1)
		move_dir = modulo_perso(map->player.dir + 2, 4);
	else if (side == 1)
		move_dir = modulo_perso(map->player.dir + 1, 4);
	else if (side == -1)
		move_dir = modulo_perso(map->player.dir - 1, 4);
	else
		move_dir = map->player.dir;
	return (move_dir);
}

float	new_pos_x(t_map *map)
{
	float	move_dir;

	move_dir = get_move_dir(map);
	if (move_dir >= NORTH && move_dir < EAST)
		return (sin(move_dir * M_PI_2) * SPEED);
	else if (move_dir >= EAST && move_dir < SOUTH)
		return (cos((move_dir - 1) * M_PI_2) * SPEED);
	else if (move_dir >= SOUTH && move_dir < WEST)
		return (-sin((move_dir - 2) * M_PI_2) * SPEED);
	else
		return (-cos((move_dir - 3) * M_PI_2) * SPEED);
}

float	new_pos_y(t_map *map)
{
	float	move_dir;

	move_dir = get_move_dir(map);
	if (move_dir >= NORTH && move_dir < EAST)
		return (-cos(move_dir * M_PI_2) * SPEED);
	else if (move_dir >= EAST && move_dir < SOUTH)
		return (sin((move_dir - 1) * M_PI_2) * SPEED);
	else if (move_dir >= SOUTH && move_dir < WEST)
		return (cos((move_dir - 2) * M_PI_2) * SPEED);
	else
		return (-sin((move_dir - 3) * M_PI_2) * SPEED);
}
