/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sprite_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:01:08 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 17:02:59 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

static void	print_full_sprite(
			t_map *map, int posx, int middle_part)
{
	int		i;
	char	*img;
	int		color;

	i = 0;
	img = mlx_get_data_addr (map->img[(int)map->anim].ptr,
			&(map->img[(int)map->anim].bits_pixel),
			&(map->img[(int)map->anim].size_line),
			&(map->img[(int)map->anim].endian));
	while (i < SCREEN_HEIGHT)
	{
		color = *(int *)(img
				+ (4 * (map->img[(int)map->anim].x) * (int)ft_map_values_f(
						i + (middle_part - SCREEN_HEIGHT) / 2,
						middle_part, map->img[(int)map->anim].y - 1))
				+ (4 * posx));
		if (color != (int)EMPTY_COLOR)
		{
			if (!map->img[(int)map->anim].endian)
				put_pixel(map->column.n, i, switch_color(color), map);
			else
				put_pixel(map->column.n, i, color, map);
		}
		i++;
	}
}

static void	print_sprite_utils(t_map *map, int posx, char *img, int middle_part)
{
	int	i;
	int	color;
	int	posy;

	i = SCREEN_HEIGHT / 2 - middle_part / 2;
	while (i < SCREEN_HEIGHT / 2 + middle_part / 2)
	{
		posy = ft_map_values(i - (SCREEN_HEIGHT / 2 - middle_part / 2),
				SCREEN_HEIGHT / 2 + middle_part / 2
				- (SCREEN_HEIGHT / 2 - middle_part / 2),
				map->img[(int)map->anim].y - 1);
		color = *(int *)(img
				+ (4 * (map->img[(int)map->anim].x) * posy)
				+ (4 * posx));
		if (color == (int)EMPTY_COLOR)
		{
			i++;
			continue ;
		}
		if (!map->img[(int)map->anim].endian)
			put_pixel(map->column.n, i, switch_color(color), map);
		else
			put_pixel(map->column.n, i, color, map);
		i++;
	}
}

static void	print_sprite(t_map *map, int posx, float len_to_sprite)
{
	int		middle_part;
	char	*img;

	img = mlx_get_data_addr (map->img[(int)map->anim].ptr,
			&(map->img[(int)map->anim].bits_pixel),
			&(map->img[(int)map->anim].size_line),
			&(map->img[(int)map->anim].endian));
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT) / len_to_sprite);
	if (middle_part >= SCREEN_HEIGHT)
		print_full_sprite(map, posx, middle_part);
	else
		print_sprite_utils(map, posx, img, middle_part);
}

void	put_sprite(t_sprite *sprite, t_map *map, float raydir)
{
	float	len_to_middle;
	float	angle_to_middle;
	float	len_to_sprite;
	float	pixel_pos;
	float	angle_diff;

	len_to_middle = sqrtf(powf(map->player.x - sprite->x - 0.5, 2)
			+ powf(map->player.y - sprite->y - 0.5, 2));
	if (map->player.y > sprite->y + 0.5)
		angle_to_middle = M_PI
			- acosf((map->player.x - sprite->x - 0.5) / len_to_middle);
	else
		angle_to_middle = M_PI
			+ acosf((map->player.x - sprite->x - 0.5) / len_to_middle);
	if (raydir > M_PI)
		raydir -= 2 * M_PI;
	angle_diff = raydir - angle_to_middle;
	len_to_sprite = len_to_middle / cos(angle_diff);
	pixel_pos = sin(angle_diff) * len_to_sprite;
	if (pixel_pos > 0.5 || pixel_pos < -0.5)
		return ;
	pixel_pos += 0.5;
	pixel_pos = ft_map_values_f(pixel_pos, 1, map->img[(int)map->anim].x);
	print_sprite(map, (int)pixel_pos, len_to_sprite);
}
