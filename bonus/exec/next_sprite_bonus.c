/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:31:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:06:23 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	print_coin_obtained(t_map *map, char *img, int n)
{
	int	i;
	int	color;

	i = 0;
	while (i < 64)
	{
		color = *(int *)(img
				+ (4 * (map->img[GOAT_COIN].x)
					* ft_map_values(i, 64, map->img[GOAT_COIN].y))
				+ (4 * ft_map_values(n, 128, map->img[GOAT_COIN].x)));
		if (color == (int)EMPTY_COLOR)
		{
			i++;
			continue ;
		}
		if (!map->img[GOAT_COIN].endian)
			put_pixel(
				SCREEN_WIDTH / 2 - 64 + n, SCREEN_HEIGHT + i - 74,
				switch_color(color), map);
		else
			put_pixel(SCREEN_WIDTH / 2 - 64 + n,
				SCREEN_HEIGHT + i - 74, color, map);
		i++;
	}
}

static int	check_is_sprite(float x, float y, t_map *map)
{
	if (!is_in_map(x, y, map))
		return (-1);
	if (map->map[(int)y][(int)x] == '4')
		return (1);
	return (0);
}

static int	check_near(float raydir, t_sprite *sprite, int mode, t_map *map)
{
	if (mode == HORIZONTAL && raydir >= 0 && raydir < M_PI)
		return (check_is_sprite(sprite->hx, sprite->hy - 0.000001, map));
	else if (mode == HORIZONTAL)
		return (check_is_sprite(sprite->hx, sprite->hy + 0.000001, map));
	else if (mode == VERTICAL && raydir >= M_PI_2 && raydir < 3 * M_PI_2)
		return (check_is_sprite(sprite->vx - 0.000001, sprite->vy, map));
	else if (mode == VERTICAL)
		return (check_is_sprite(sprite->vx + 0.000001, sprite->vy, map));
	return (-1);
}

int	new_sprite_pos(float raydir, t_sprite *sprite, int mode, t_map *map)
{
	if (mode == HORIZONTAL && raydir >= 0 && raydir < M_PI)
	{
		sprite->hx += 1 / tan(raydir);
		sprite->hy -= 1;
	}
	else if (mode == HORIZONTAL)
	{
		sprite->hx -= 1 / tan(raydir);
		sprite->hy += 1;
	}
	else if (mode == VERTICAL && raydir >= M_PI_2 && raydir < 3 * M_PI_2)
	{
		sprite->vx -= 1;
		sprite->vy += tan(raydir);
	}
	else if (mode == VERTICAL)
	{
		sprite->vx += 1;
		sprite->vy -= tan(raydir);
	}
	return (check_near(raydir, sprite, mode, map));
}
