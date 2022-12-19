/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 17:21:01 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	set_wall_color(t_map *map, int n, int i)
{
	int		posx;
	int		posy;
	char	*img;
	int		color;

	wall_color_img(map, &img);
	posx = ft_map_values(map->wall_pos, 1, map->img[map->wall_color].x - 1);
	posy = ft_map_values(i - map->column.start,
			SCREEN_HEIGHT / 2 + map->column.height / 2 - map->column.start,
			map->img[map->wall_color].y - 1);
	color = *(int *)(img
			+ (4 * (map->img[map->wall_color].x) * posy)
			+ (4 * posx));
	if (!map->img[map->wall_color].endian)
		put_pixel(n, i, switch_color(color), map);
	else
		put_pixel(n, i, color, map);
}

void	set_wall_color_full(t_map *map, int n, int i)
{
	int		posx;
	int		posy;
	int		diff;
	char	*img;
	int		color;

	wall_color_img(map, &img);
	posx = ft_map_values(map->wall_pos, 1, map->img[map->wall_color].x - 1);
	diff = map->column.height - SCREEN_HEIGHT;
	posy = i + diff / 2;
	posy = ft_map_values(posy, map->column.height,
			map->img[map->wall_color].y - 1);
	color = *(int *)(img
			+ (4 * (map->img[map->wall_color].x) * posy)
			+ (4 * posx));
	if (!map->img[map->wall_color].endian)
		put_pixel(n, i, switch_color(color), map);
	else
		put_pixel(n, i, color, map);
}

static float	ray_len(t_map *map, float raydir)
{
	float	posx;
	float	posy;

	posx = (int)map->player.x;
	posy = (int)map->player.y;
	if (raydir > 0 && raydir < 1)
		return (ray_split_ne(map, raydir, &posx, &posy));
	else if (raydir > 1 && raydir < 2)
		return (ray_split_se(map, raydir, &posx, &posy));
	else if (raydir > 2 && raydir < 3)
		return (ray_split_sw(map, raydir, &posx, &posy));
	else
		return (ray_split_nw(map, raydir, &posx, &posy));
}

void	raycast(int n, t_map *map, float raydir)
{
	int		middle_part;
	float	raylen;
	int		i;

	map->column.n = n;
	if (raydir - (int)raydir == 0)
		raydir += 0.0001;
	raylen = ray_len(map, raydir);
	map->column.raylen = raylen * cos(
			modulo_perso(map->player.dir - raydir, 4) * M_PI_2);
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT) / map->column.raylen);
	i = 0;
	map->column.height = middle_part;
	if (middle_part >= SCREEN_HEIGHT)
	{
		while (i < SCREEN_HEIGHT)
		{
			set_wall_color_full(map, n, i);
			i++;
		}
		return ;
	}
	raycast_utils(map, middle_part, raylen, raydir);
}
