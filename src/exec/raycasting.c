/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 18:26:23 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	set_wall_color(t_map *map, int x, int y)
{
	int				pixel;
	unsigned char	*color_buf;

	color_buf = (unsigned char *)&(map->wall_color);
	pixel = (y * map->line_bytes) + (x * 4);
	map->buffer[pixel] = color_buf[3];
	map->buffer[pixel + 1] = color_buf[2];
	map->buffer[pixel + 2] = color_buf[1];
	map->buffer[pixel + 3] = (unsigned char)0;
}

void	put_pixel(int x, int y, int color, t_map *map)
{
	int				pixel;
	unsigned char	*color_buf;

	pixel = (y * map->line_bytes) + (x * 4);
	color_buf = (unsigned char *)&color;
	map->buffer[pixel] = color_buf[3];
	map->buffer[pixel + 1] = color_buf[2];
	map->buffer[pixel + 2] = color_buf[1];
	map->buffer[pixel + 3] = (unsigned char)0;
}

static void		ray_len_next(
			t_map *map, float raydir, float *new_pos_x, float *new_pos_y)
{
	while (raydir > 2 && raydir < 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * sin((raydir - 2) * M_PI_2);
		*new_pos_y += 0.01 * cos((raydir - 2) * M_PI_2);
	}
	while (raydir > 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * cos((raydir - 3) * M_PI_2);
		*new_pos_y -= 0.01 * sin((raydir - 3) * M_PI_2);
	}
}

static float	ray_len(t_map *map, float raydir)
{
	float	new_pos_x;
	float	new_pos_y;
	float	len;

	new_pos_x = map->player.x;
	new_pos_y = map->player.y;
	while (raydir > 0 && raydir < 1 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * sin(raydir * M_PI_2);
		new_pos_y -= 0.01 * cos(raydir * M_PI_2);
	}
	while (raydir > 1 && raydir < 2 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * cos((raydir - 1) * M_PI_2);
		new_pos_y += 0.01 * sin((raydir - 1) * M_PI_2);
	}
	ray_len_next(map, raydir, &new_pos_x, &new_pos_y);
	len = sqrtf(powf(map->player.x - new_pos_x, 2) + 
		powf(map->player.y - new_pos_y, 2));
	return (len);
}

void	raycast(int n, t_map *map, float raydir)
{
	float	len_ray;
	int		middle_part;
	int		i;

	if (raydir - (int)raydir == 0)
		raydir += 0.00001;
	len_ray = ray_len(map, raydir);
	len_ray *= cos(modulo_perso(map->player.dir - raydir, 4) * M_PI_2);
	get_wall_color(map, raydir);
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT )/len_ray);
	i = 0;
	if (middle_part >= SCREEN_HEIGHT)
	{
		while (i < SCREEN_HEIGHT)
		{
			set_wall_color(map, n, i);
			i++;
		}
		return ;
	}
	while (i < SCREEN_HEIGHT/2 - middle_part/2)
	{
		put_pixel(n, i, map->ceiling, map);
		i++;
	}
	while (i < SCREEN_HEIGHT/2 + middle_part/2)
	{
		set_wall_color(map, n, i);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		put_pixel(n, i, map->floor, map);
		i++;
	}
}