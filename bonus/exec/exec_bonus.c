/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:55:09 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/17 20:16:16 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"
#include <sys/wait.h>

void	put_big_minimap(t_map *map)
{
	int		start_point_x;
	int		start_point_y;
	float	n;
	float	i;

	//map
	n = 0;
	start_point_x = 10 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
	start_point_y = 10;
	while (n < SCREEN_HEIGHT - 20)
	{
		i = 0;
		while (i < SCREEN_HEIGHT - 20)
		{
			if (sqrt(powf(n/((SCREEN_HEIGHT - 10)/32) - 16, 2) + powf(i/((SCREEN_HEIGHT - 10)/32) - 16, 2)) > 15)
			{
					i++;
					continue ;
			}
			else if (!is_in_map(
					map->player.x - 16 + n/((SCREEN_HEIGHT - 10)/32), map->player.y - 16 + i/((SCREEN_HEIGHT - 10)/32), map)
					|| sqrt(powf(n/((SCREEN_HEIGHT - 10)/32) - 16, 2) + powf(i/((SCREEN_HEIGHT - 10)/32) - 16, 2)) > 14.5)
				put_pixel(start_point_x + n, start_point_y + i, 0x00000000, map);
			else if (is_wall(map,
					map->player.x - 16 + n/((SCREEN_HEIGHT - 10)/32), map->player.y - 16 + i/((SCREEN_HEIGHT - 10)/32)))
				put_pixel(start_point_x + n, start_point_y + i, map->floor, map);
			else if (is_door(map,
					map->player.x - 16 + n/((SCREEN_HEIGHT - 10)/32), map->player.y - 16 + i/((SCREEN_HEIGHT - 10)/32)))
				put_pixel(start_point_x + n, start_point_y + i, 0x0099FF00, map);
			else
				put_pixel(start_point_x + n, start_point_y + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
	//rayon
	start_point_x = SCREEN_WIDTH/2;
	start_point_y = SCREEN_HEIGHT/2;
	n = 0;
	while (n < 30)
	{
		put_pixel(start_point_x + (n * sin(map->player.dir/4 * M_PI * 2)),
					start_point_y - (n * cos(map->player.dir/4 * M_PI * 2)),
					0x0000FF00, map);
		n++;
	}
	//player
	start_point_x -= 5;
	start_point_y -= 6;
	n = 0;
	while (n < 12)
	{
		i = 0;
		while (i < 13)
		{
			put_pixel(start_point_x + n, start_point_y + i, 0x00000000, map);
			i++;
		}
		n++;
	}
}

void	put_minimap(t_map *map)
{
	int		start_point_x;
	int		start_point_y;
	float	n;
	float	i;

	//map
	n = 0;
	start_point_x = 10;
	start_point_y = 10;
	while (n < 200)
	{
		i = 0;
		while (i < 200)
		{
			if (sqrt(powf(n/12.5 - 8, 2) + powf(i/12.5 - 8, 2)) > 8)
			{
					i++;
					continue ;
			}
			else if (!is_in_map(
					map->player.x - 8 + n/12.5, map->player.y - 8 + i/12.5, map)
					|| sqrt(powf(n/12.5 - 8, 2) + powf(i/12.5 - 8, 2)) > 7.7)
				put_pixel(start_point_x + n, start_point_y + i, 0x00000000, map);
			else if (is_wall(map,
					map->player.x - 8 + n/12.5, map->player.y - 8 + i/12.5))
				put_pixel(start_point_x + n, start_point_y + i, map->floor, map);
			else if (is_door(map,
					map->player.x - 8 + n/12.5, map->player.y - 8 + i/12.5))
				put_pixel(start_point_x + n, start_point_y + i, 0x0099FF00, map);
			else
				put_pixel(start_point_x + n, start_point_y + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
	//rayon
	start_point_x += 100;
	start_point_y += 100;
	n = 0;
	while (n < 15)
	{
		put_pixel(start_point_x + (n * sin(map->player.dir/4 * M_PI * 2)),
					start_point_y - (n * cos(map->player.dir/4 * M_PI * 2)),
					0x0000FF00, map);
		n++;
	}
	//player
	start_point_x -= 2;
	start_point_y -= 3;
	n = 0;
	while (n < 5)
	{
		i = 0;
		while (i < 6)
		{
			put_pixel(start_point_x + n, start_point_y + i, 0x00000000, map);
			i++;
		}
		n++;
	}
}

void	put_crosshair(t_map *map)
{
	int	start_point_x;
	int	start_point_y;
	int	n;
	int	i;

	n = 0;
	start_point_x = SCREEN_WIDTH/2 - CROSSHAIR_SIZE + 1;
	start_point_y = SCREEN_HEIGHT/2 - 2;
	while (n < CROSSHAIR_SIZE * 2 - 2)
	{
		i = 0;
		while (i < 3)
		{
			put_pixel(start_point_x + n, start_point_y + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
	n = 0;
	start_point_x = SCREEN_WIDTH/2 - 1;
	start_point_y = SCREEN_HEIGHT/2 - CROSSHAIR_SIZE;
	while (n < 2)
	{
		i = 0;
		while (i < CROSSHAIR_SIZE * 2 - 1)
		{
			put_pixel(start_point_x + n, start_point_y + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
}

void	refresh_screen(t_map *map)
{
	int		n;
	float	raydir;

	n = 0;
	while (n < SCREEN_WIDTH)
	{
		raydir = modulo_perso(
				map->player.dir + (n - SCREEN_WIDTH/2) * 0.5 / SCREEN_WIDTH, 4);
		raycast(n, map, raydir);
		n+=2;
	}
	if (!map->minimap)
	{
		put_minimap(map);
		put_crosshair(map);
	}
	else
		put_big_minimap(map);
}

static int	game_loop(t_map *map)
{
	float	posx;
	float	posy;
	float	rotation;

	if (map->player.open)
		manahge_door(map);
	map->anim += ANIM_SPEED;
	if ((int)map->anim > ANIM6)
		map->anim = ANIM1;
	rotation = ft_map_values_f(map->player.pos_turn, SCREEN_WIDTH, 4) * 0.15;
	map->player.dir = modulo_perso(map->player.dir + rotation, 4);
	map->player.pos_turn = 0;
	if (map->player.trigo - map->player.antitrigo)
		map->player.dir = modulo_perso(map->player.dir
			+ (map->player.antitrigo - map->player.trigo) * TURN_SPEED, 4);
	if (map->player.forward || map->player.backward || map->player.right
		|| map->player.left)
	{
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
	refresh_screen(map);
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	return (0);
}

int	new_game(t_map *map)
{
	map->vars.mlx = mlx_init();
	if (!textures_init_xpm(map))
		return (1);
	map->vars.win = mlx_new_window(
				map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_mouse_move(map->vars.win, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	mlx_mouse_hide();
	mlx_hook(map->vars.win, 17, 0, end_exec, map);
	mlx_hook(map->vars.win, 2, 0, event_key_pressed, map);
	mlx_hook(map->vars.win, 3, 0, event_key_released, map);
	mlx_hook(map->vars.win, 6, 0, mouse_move, map);
	map->vars.screen = mlx_new_image(
				map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->buffer = mlx_get_data_addr(map->vars.screen, &(map->pixel_bits), &(map->line_bytes), &(map->endian));
	mlx_loop_hook(map->vars.mlx, game_loop, map);
	mlx_loop(map->vars.mlx);
	return (0);
}
