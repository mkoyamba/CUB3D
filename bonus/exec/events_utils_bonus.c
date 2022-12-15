/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:29:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/14 16:04:07 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

int	end_exec(t_map *map)
{
	free_struct_map(map);
	ft_putendl_fd("Fin de la partie.\nMerci d'avoir joué.", 1);
	exit(0);
	return (0);
}

int	mouse_move(int x, int y, t_map *map)
{
	(void)y;
	if (x >= 0 && x <= SCREEN_WIDTH)
		map->player.pos_turn = x - SCREEN_WIDTH/2;
	else if (x < 0)
		map->player.pos_turn = 0;
	else
		map->player.pos_turn = SCREEN_WIDTH;
	mlx_mouse_move(map->vars.win, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	return (0);
}

int	event_key_pressed(int keycode, t_map *map)
{
	if (keycode == 53)
		end_exec(map);
	else if (keycode == 2)
		map->player.right = 1;
	else if (keycode == 48)
		map->minimap = 1;
	else if (keycode == 0)
		map->player.left = 1;
	else if (keycode == 13)
		map->player.forward = 1;
	else if (keycode == 1)
		map->player.backward = 1;
	else if (keycode == 12 || keycode == 123)
		map->player.trigo = 1;
	else if (keycode == 14 || keycode == 124)
		map->player.antitrigo = 1;
	return (0);
}

int	event_key_released(int keycode, t_map *map)
{
	if (keycode == 2)
		map->player.right = 0;
	else if (keycode == 0)
		map->player.left = 0;
	else if (keycode == 48)
		map->minimap = 0;
	else if (keycode == 13)
		map->player.forward = 0;
	else if (keycode == 1)
		map->player.backward = 0;
	else if (keycode == 12 || keycode == 123)
		map->player.trigo = 0;
	else if (keycode == 14 || keycode == 124)
		map->player.antitrigo = 0;
	else if (keycode == 3 || keycode == 49)
		map->player.open = 1;
	return (0);
}
