/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:30:08 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/09 21:33:46 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

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
	float	posx;
	float	posy;
	float	test_len_ray;
	float	dir;

	dir = ft_map_values_f(map->player.dir, 4, 1);
	map->player.open = 0;
	raycast(SCREEN_WIDTH/2, map, map->player.dir);
	if ((map->column.type == '3' || map->column.type == '2')
			&& map->column.raylen < 2.5)
	{
		test_len_ray = 0;
		posx = map->player.x;
		posy = map->player.y;
		while (test_len_ray < 2.5)
		{
			test_len_ray += 0.01;
			posx = sin(dir * M_PI * 2) * test_len_ray + map->player.x;
			posy = (- cos(dir * M_PI * 2)) * test_len_ray + map->player.y;
			if (map->map[(int)posy][(int)posx] == '3')
			{
				map->map[(int)posy][(int)posx] = '2';
				break ;
			}
			else if (map->map[(int)posy][(int)posx] == '2')
			{
				map->map[(int)posy][(int)posx] = '3';
				break ;
			}
		}
		refresh_screen(map);
		mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	}
}
