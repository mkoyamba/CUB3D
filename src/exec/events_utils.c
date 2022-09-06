/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:29:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 18:50:28 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	end_exec(t_map *map)
{
	free_struct_map(map);
	ft_putendl_fd("Je finis.", 1);
	exit(0);
	return (0);
}

int	event_key_pressed(int keycode, t_map *map)
{
	if (keycode == 53)
		end_exec(map);
	if (keycode == 2)
		map->player.right = 1;
	if (keycode == 0)
		map->player.left = 1;
	if (keycode == 13)
		map->player.forward = 1;
	if (keycode == 1)
		map->player.backward = 1;
	if (keycode == 12 || keycode == 123)
		map->player.trigo = 1;
	if (keycode == 14 || keycode == 124)
		map->player.antitrigo = 1;
	return (0);
}

int	event_key_released(int keycode, t_map *map)
{
	if (keycode == 2)
		map->player.right = 0;
	if (keycode == 0)
		map->player.left = 0;
	if (keycode == 13)
		map->player.forward = 0;
	if (keycode == 1)
		map->player.backward = 0;
	if (keycode == 12 || keycode == 123)
		map->player.trigo = 0;
	if (keycode == 14 || keycode == 124)
		map->player.antitrigo = 0;
	return (0);
}
