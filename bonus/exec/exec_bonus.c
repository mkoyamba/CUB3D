/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:55:09 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:08:20 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	print_map(t_map *map, float n, float i)
{
	if (!is_in_map(
			map->player.x - 8 + n / 12.5,
			map->player.y - 8 + i / 12.5, map)
		|| sqrt(powf(n / 12.5 - 8, 2)
			+ powf(i / 12.5 - 8, 2)) > 7.7)
		put_pixel(10 + n, 10 + i, 0x00000000, map);
	else if (is_wall(map,
			map->player.x - 8 + n / 12.5, map->player.y - 8 + i / 12.5))
		put_pixel(10 + n, 10 + i, map->floor, map);
	else if (is_door(map,
			map->player.x - 8 + n / 12.5, map->player.y - 8 + i / 12.5))
		put_pixel(10 + n, 10 + i, 0x0099FF00, map);
	else if (is_coin(map,
			map->player.x - 8 + n / 12.5, map->player.y - 8 + i / 12.5))
		put_pixel(10 + n, 10 + i, 0x00CCFF00, map);
	else
		put_pixel(10 + n, 10 + i, CROSSHAIR_COLOR, map);
}

void	print_ray_player(t_map *map)
{
	int	n;
	int	i;

	n = 0;
	while (n < 15)
	{
		put_pixel(110 + (n * sin(map->player.dir / 4 * M_PI * 2)),
			110 - (n * cos(map->player.dir / 4 * M_PI * 2)),
			0x0000FF00, map);
		n++;
	}
	n = 0;
	while (n < 5)
	{
		i = 0;
		while (i < 6)
		{
			put_pixel(108 + n, 108 + i, 0x00000000, map);
			i++;
		}
		n++;
	}
}

void	put_minimap(t_map *map)
{
	float	n;
	float	i;

	n = 0;
	while (n < 200)
	{
		i = 0;
		while (i < 200)
		{
			if (sqrt(powf(n / 12.5 - 8, 2) + powf(i / 12.5 - 8, 2)) < 8)
				print_map(map, n, i);
			i++;
		}
		n++;
	}
	print_ray_player(map);
}

void	game_loop_new_pos(t_map *map)
{
	float	posx;
	float	posy;

	posx = map->player.x + new_pos_x(map);
	posy = map->player.y + new_pos_y(map);
	if (is_valid_pos_player(map, map->player.x + new_colision_x(map),
			map->player.y + new_colision_y(map)))
	{
		map->player.x = posx;
		map->player.y = posy;
	}
	else
	{
		if (is_valid_pos_player(map, map->player.x + new_colision_x(map),
				map->player.y))
			map->player.x = posx;
		else if (is_valid_pos_player(map, map->player.x,
				map->player.y + new_colision_y(map)))
			map->player.y = posy;
	}
}

int	game_loop(t_map *map)
{
	float	rotation;

	if (map->player.open)
		manahge_door(map);
	map->anim += ANIM_SPEED;
	if ((int)map->anim > ANIM6)
		map->anim = ANIM1;
	if (map->map[(int)map->player.y][(int)map->player.x] == '4'
		|| map->got_coin > 0)
		get_coin(map);
	rotation = ft_map_values_f(map->player.pos_turn, SCREEN_WIDTH, 4) * 0.15;
	map->player.dir = modulo_perso(map->player.dir + rotation, 4);
	map->player.pos_turn = 0;
	if (map->player.trigo - map->player.antitrigo)
		map->player.dir = modulo_perso(map->player.dir
				+ (map->player.antitrigo - map->player.trigo) * TURN_SPEED, 4);
	if (map->player.forward || map->player.backward || map->player.right
		|| map->player.left)
		game_loop_new_pos(map);
	refresh_screen(map);
	mlx_put_image_to_window(
		map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	put_coins(map);
	return (0);
}
