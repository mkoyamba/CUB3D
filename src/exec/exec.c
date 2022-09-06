/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:55:09 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 00:05:35 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include <sys/wait.h>

static void	refresh_screen(t_map *map)
{
	int		n;
	float	raydir;

	n = 0;
	while (n < 1600)
	{
		raydir = modulo_perso(map->player.dir + (n - 800) * 0.3 / 800, 4);
		raycast(n, map, raydir);
		n++;
	}
}

static int	game_loop(t_map *map)
{
	float	posx;
	float	posy;

	if (map->player.trigo - map->player.antitrigo)
	{
		map->player.dir = modulo_perso(map->player.dir
			+ (map->player.antitrigo - map->player.trigo) * TURN_SPEED, 4);
		if (fabs(map->player.dir - map->player.before_dir) > 0.4)
			map->refresh = 1;
	}
	if (map->player.forward || map->player.backward || map->player.right
		|| map->player.left)
	{
		posx = map->player.x + new_pos_x(map);
		posy = map->player.y + new_pos_y(map);
		if (is_valid_pos(map, posx, posy))
		{
			map->player.x = posx;
			map->player.y = posy;
			if (fabs(map->player.before_x - posx)
				+ fabs(map->player.before_y - posy) > 0.01)
				map->refresh = 1;
		}
	}
	if (map->refresh == 1)
	{
		map->player.before_x = map->player.x;
		map->player.before_y = map->player.y;
		map->player.before_dir = map->player.dir;
		map->refresh = 0;
		refresh_screen(map);
	}
	usleep(500000);
	return (0);
}

int	new_game(t_map *map)
{
	map->player.right = 0;
	map->player.left = 0;
	map->player.forward = 0;
	map->player.backward = 0;
	map->player.trigo = 0;
	map->player.antitrigo = 0;
	map->player.before_x = map->player.x;
	map->player.before_y = map->player.y;
	map->player.before_dir = map->player.dir;
	map->refresh = 1;
	map->vars.mlx = mlx_init();
	map->vars.win = mlx_new_window(map->vars.mlx, 1600, 900, "Cub3d");
	mlx_hook(map->vars.win, 17, 0, end_exec, map);
	mlx_hook(map->vars.win, 2, 0, event_key_pressed, map);
	mlx_hook(map->vars.win, 3, 0, event_key_released, map);
	map->vars.screen = mlx_new_image(map->vars.mlx, 1600, 900);
	mlx_loop_hook(map->vars.mlx, game_loop, map);
	mlx_loop(map->vars.mlx);
	return (0);
}
