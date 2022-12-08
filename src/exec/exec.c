/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:55:09 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/07 19:13:18 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"
#include <sys/wait.h>

static void	refresh_screen(t_map *map)
{
	int		n;
	float	raydir;

	n = 0;
	while (n < SCREEN_WIDTH)
	{
		raydir = modulo_perso(
				map->player.dir + (n - SCREEN_WIDTH/2) * 0.5 / SCREEN_WIDTH, 4);
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
		map->refresh = 1;
	}
	if (map->player.forward || map->player.backward || map->player.right
		|| map->player.left)
	{
		posx = map->player.x + new_pos_x(map);
		posy = map->player.y + new_pos_y(map);
		if (is_valid_pos(map, map->player.x + new_colision_x(map),
					map->player.y + new_colision_y(map)))
		{
			map->player.x = posx;
			map->player.y = posy;
			map->refresh = 1;
		}
		else
		{
			if (is_valid_pos(map, map->player.x + new_colision_x(map),
					map->player.y))
			{
				map->player.x = posx;
				map->refresh = 1;
			}
			else if (is_valid_pos(map, map->player.x,
						map->player.y + new_colision_y(map)))
			{
				map->player.y = posy;
				map->refresh = 1;
			}
		}
	}
	if (map->refresh == 1)
	{
		map->refresh = 0;
		refresh_screen(map);
		mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	}
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
	map->player.x += 0.5;
	map->player.y += 0.5;
	map->refresh = 1;
	map->vars.mlx = mlx_init();
	if (!textures_init_xpm(map))
		return (1);
	map->vars.win = mlx_new_window(
				map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_hook(map->vars.win, 17, 0, end_exec, map);
	mlx_hook(map->vars.win, 2, 0, event_key_pressed, map);
	mlx_hook(map->vars.win, 3, 0, event_key_released, map);
	map->vars.screen = mlx_new_image(
				map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->buffer = mlx_get_data_addr(map->vars.screen, &(map->pixel_bits), &(map->line_bytes), &(map->endian));
	mlx_loop_hook(map->vars.mlx, game_loop, map);
	mlx_loop(map->vars.mlx);
	return (0);
}
