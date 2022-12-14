/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 15:29:56 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	set_wall_color(t_map *map, int n, int i)
{
	int		posx;
	int		posy;
	char	*img;
	int		color;

	img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
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

	img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
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

void	put_pixel(int x, int y, int color, t_map *map)
{
	int				pixel;
	unsigned char	*color_buf;
	int				iter;

	iter = 0;
	while (iter < 2)
	{
		pixel = (y * map->line_bytes) + ((x + iter) * 4);
		color_buf = (unsigned char *)&color;
		map->buffer[pixel] = color_buf[3];
		map->buffer[pixel + 1] = color_buf[2];
		map->buffer[pixel + 2] = color_buf[1];
		map->buffer[pixel + 3] = (unsigned char)0;
		iter++;
	}
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
	float	len_ray;
	int		middle_part;
	int		i;

	if (raydir - (int)raydir == 0)
		raydir += 0.0001;
	len_ray = ray_len(map, raydir);
	len_ray *= cos(modulo_perso(map->player.dir - raydir, 4) * M_PI_2);
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT) / len_ray);
	i = 0;
	map->column.height = middle_part;
	while (i < (SCREEN_HEIGHT - middle_part) * 30)
		i++;
	i = 0;
	if (middle_part >= SCREEN_HEIGHT)
	{
		while (i < SCREEN_HEIGHT)
		{
			set_wall_color_full(map, n, i);
			i++;
		}
		return ;
	}
	raycast_draw_wall(n, i, map, middle_part);
}
