/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_more_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:07:11 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 18:26:13 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	wall_color_img(t_map *map, char **img)
{
	if (map->column.type == '1')
	{
		*img = mlx_get_data_addr (map->img[map->wall_color].ptr,
				&(map->img[map->wall_color].bits_pixel),
				&(map->img[map->wall_color].size_line),
				&(map->img[map->wall_color].endian));
	}
	else if (map->column.type == '2')
	{
		map->wall_color = CLOSED;
		*img = mlx_get_data_addr (map->img[map->wall_color].ptr,
				&(map->img[map->wall_color].bits_pixel),
				&(map->img[map->wall_color].size_line),
				&(map->img[map->wall_color].endian));
	}
	else
	{
		map->wall_color = OPENED;
		*img = mlx_get_data_addr (map->img[map->wall_color].ptr,
				&(map->img[map->wall_color].bits_pixel),
				&(map->img[map->wall_color].size_line),
				&(map->img[map->wall_color].endian));
	}
}

void	raycast_utils(t_map *map, int middle_part, float raylen, float raydir)
{
	int	i;

	i = 0;
	while (i < SCREEN_HEIGHT / 2 - middle_part / 2)
	{
		put_pixel(map->column.n, i, map->ceiling, map);
		i++;
	}
	map->column.start = i;
	while (i < SCREEN_HEIGHT / 2 + middle_part / 2)
	{
		set_wall_color(map, map->column.n, i);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		put_pixel(map->column.n, i, map->floor, map);
		i++;
	}
	if (map->column.is_sprite)
		sprite_draw(map, raylen, raydir);
	map->column.is_sprite = 0;
}

static void	print_big_map(t_map *map, float n, float i)
{
	int	start_x;

	start_x = 10 + (SCREEN_WIDTH - SCREEN_HEIGHT) / 2;
	if (!is_in_map(
			map->player.x - 16 + n / ((SCREEN_HEIGHT - 10) / 32),
			map->player.y - 16 + i / ((SCREEN_HEIGHT - 10) / 32),
			map)
		|| sqrt(powf(n / ((SCREEN_HEIGHT - 10) / 32) - 16, 2)
			+ powf(i / ((SCREEN_HEIGHT - 10) / 32) - 16, 2)) > 14.5)
		put_pixel(start_x + n, 10 + i, 0x00000000, map);
	else if (is_wall(map,
			map->player.x - 16 + n / ((SCREEN_HEIGHT - 10) / 32),
			map->player.y - 16 + i / ((SCREEN_HEIGHT - 10) / 32)))
		put_pixel(start_x + n, 10 + i, map->floor, map);
	else if (is_door(map,
			map->player.x - 16 + n / ((SCREEN_HEIGHT - 10) / 32),
			map->player.y - 16 + i / ((SCREEN_HEIGHT - 10) / 32)))
		put_pixel(start_x + n, 10 + i, 0x0099FF00, map);
	else if (is_coin(map,
			map->player.x - 16 + n / ((SCREEN_HEIGHT - 10) / 32),
			map->player.y - 16 + i / ((SCREEN_HEIGHT - 10) / 32)))
		put_pixel(start_x + n, 10 + i, 0x00CCFF00, map);
	else
		put_pixel(start_x + n, 10 + i, CROSSHAIR_COLOR, map);
}

static void	print_big_ray_player(t_map *map)
{
	int	n;
	int	i;

	n = 0;
	while (n < 30)
	{
		put_pixel(SCREEN_WIDTH / 2 + (n * sin(map->player.dir / 4 * M_PI * 2)),
			SCREEN_HEIGHT / 2 - (n * cos(map->player.dir / 4 * M_PI * 2)),
			0x0000FF00, map);
		n++;
	}
	n = 0;
	while (n < 12)
	{
		i = 0;
		while (i < 13)
		{
			put_pixel(SCREEN_WIDTH / 2 - 5 + n,
				SCREEN_HEIGHT / 2 - 6 + i, 0x00000000, map);
			i++;
		}
		n++;
	}
}

void	put_big_minimap(t_map *map)
{
	float	n;
	float	i;

	n = 0;
	while (n < SCREEN_HEIGHT - 20)
	{
		i = 0;
		while (i < SCREEN_HEIGHT - 20)
		{
			if (sqrt(powf(n / ((SCREEN_HEIGHT - 10) / 32) - 16, 2)
					+ powf(i / ((SCREEN_HEIGHT - 10) / 32) - 16, 2)) < 15)
				print_big_map(map, n, i);
			i++;
		}
		n++;
	}
	print_big_ray_player(map);
}
