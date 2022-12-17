/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/17 12:23:38 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

int	switch_color(int color)
{
	unsigned char	*color_buf;
	unsigned char	temp;

	color_buf = (unsigned char *)&color;
	temp = color_buf[3];
	color_buf[3] = color_buf[0];
	color_buf[0] = temp;
	temp = color_buf[1];
	color_buf[1] = color_buf[2];
	color_buf[2] = temp;
	return (color);
}

void	set_wall_color(t_map *map, int n, int i)
{
	int		posx;
	int		posy;
	char	*img;
	int		color;

	if (map->column.type == '1')
	{
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	else if (map->column.type == '2')
	{
		map->wall_color = CLOSED;
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	else
	{
		map->wall_color = OPENED;
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	posx = ft_map_values(map->wall_pos, 1, map->img[map->wall_color].x - 1);
	posy = ft_map_values(i - map->column.start,
			SCREEN_HEIGHT/2 + map->column.height/2 - map->column.start,
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

	if (map->column.type == '1')
	{
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	else if (map->column.type == '2')
	{
		map->wall_color = CLOSED;
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	else
	{
		map->wall_color = OPENED;
		img = mlx_get_data_addr (map->img[map->wall_color].ptr,
			&(map->img[map->wall_color].bits_pixel),
			&(map->img[map->wall_color].size_line),
			&(map->img[map->wall_color].endian));
	}
	posx = ft_map_values(map->wall_pos, 1, map->img[map->wall_color].x - 1);
	diff = map->column.height - SCREEN_HEIGHT;
	posy = i + diff/2;
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
	while(iter < 2)
	{
		pixel = (y * map->line_bytes) + ((x + iter) * 4) ;
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
	int		middle_part;
	float	raylen;
	int		i;

	map->column.n = n;
	if (raydir - (int)raydir == 0)
		raydir += 0.0001;
	raylen = ray_len(map, raydir);
	map->column.raylen = raylen * cos(modulo_perso(map->player.dir - raydir, 4) * M_PI_2);
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT)/map->column.raylen);
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
	while (i < SCREEN_HEIGHT/2 - middle_part/2)
	{
		put_pixel(n, i, map->ceiling, map);
		i++;
	}
	map->column.start = i;
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
	if (map->column.is_sprite)
		sprite_draw(map, raylen, raydir);
	map->column.is_sprite = 0;
}
