/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:42:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/17 20:16:55 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	print_full_sprite(
			t_map *map, int posx, int middle_part)
{
	int		i;
	int		diff;
	char	*img;
	int		posy;
	int		color;

	i = 0;
	img = mlx_get_data_addr (map->img[(int)map->anim].ptr,
			&(map->img[(int)map->anim].bits_pixel),
			&(map->img[(int)map->anim].size_line),
			&(map->img[(int)map->anim].endian));
	while (i < SCREEN_HEIGHT)
	{
		diff = middle_part - SCREEN_HEIGHT;
		posy = i + diff/2;
		posy = (int)ft_map_values_f(posy, middle_part,
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


void	print_sprite(t_map *map, int posx, float len_to_sprite)
{
	int		i;
	int		middle_part;
	char	*img;
	int		posy;
	int		color;

	img = mlx_get_data_addr (map->img[(int)map->anim].ptr,
			&(map->img[(int)map->anim].bits_pixel),
			&(map->img[(int)map->anim].size_line),
			&(map->img[(int)map->anim].endian));
	middle_part = (int)((CUBE_SIZE * SCREEN_HEIGHT)/len_to_sprite);
	if (middle_part >= SCREEN_HEIGHT)
	{
		print_full_sprite(map, posx, middle_part);
		return ;
	}
	i = SCREEN_HEIGHT/2 - middle_part/2;
	while (i < SCREEN_HEIGHT/2 + middle_part/2)
	{
		posy = ft_map_values(i - (SCREEN_HEIGHT/2 - middle_part/2),
			SCREEN_HEIGHT/2 + middle_part/2 - (SCREEN_HEIGHT/2 - middle_part/2),
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
		angle_to_middle = M_PI - acosf((map->player.x - sprite->x - 0.5) / len_to_middle);
	else
		angle_to_middle = M_PI + acosf((map->player.x - sprite->x - 0.5) / len_to_middle);
	if (raydir > M_PI)
		raydir -= 2 * M_PI;
	angle_diff =  raydir - angle_to_middle;
	len_to_sprite = len_to_middle / cos(angle_diff);
	pixel_pos = sin(angle_diff) * len_to_sprite;
	if (pixel_pos > 0.5 || pixel_pos < - 0.5)
		return ;
	pixel_pos += 0.5;
	pixel_pos = ft_map_values_f(pixel_pos, 1, map->img[(int)map->anim].x);
	print_sprite(map, (int)pixel_pos, len_to_sprite);
}

int	next_sprite(t_sprite *sprite, t_map *map, float raylen, float raydir)
{
	int	stateH;
	int	stateV;

	stateH = new_sprite_pos(raydir, sprite, HORIZONTAL, map);
	stateV = new_sprite_pos(raydir, sprite, VERTICAL, map);
	while (!stateH)
		stateH = new_sprite_pos(raydir, sprite, HORIZONTAL, map);
	while (!stateV)
		stateV = new_sprite_pos(raydir, sprite, VERTICAL, map);
	sprite->h_raylen = sqrtf(powf(sprite->start_x - sprite->Hx, 2)
							+ powf(sprite->start_y - sprite->Hy, 2));
	sprite->v_raylen = sqrtf(powf(sprite->start_x - sprite->Vx, 2)
							+ powf(sprite->start_y - sprite->Vy, 2));
	if ((stateH != 1 && stateV != 1)
		|| (sprite->h_raylen >= raylen && sprite->v_raylen >= raylen))
		return (0);
	if (sprite->h_raylen > 0 && (sprite->h_raylen < sprite->v_raylen || sprite->v_raylen < 0))
	{
		sprite->Vx = sprite->current_Vx;
		sprite->Vy = sprite->current_Vy;
		sprite->current_Hx = sprite->Hx;
		sprite->current_Hy = sprite->Hy;
		if (raydir >= 0 && raydir < M_PI)
		{
			sprite->x = (int)sprite->current_Hx;
			sprite->y = (int)(sprite->current_Hy - 0.000001);
		}
		else
		{
			sprite->x = (int)sprite->current_Hx;
			sprite->y = (int)(sprite->current_Hy + 0.000001);
		}
	}
	else
	{
		sprite->Hx = sprite->current_Hx;
		sprite->Hy = sprite->current_Hy;
		sprite->current_Vx = sprite->Vx;
		sprite->current_Vy = sprite->Vy;
		if (raydir >= M_PI_2 && raydir < 3 * M_PI_2)
		{
			sprite->x = (int)(sprite->current_Vx - 0.000001);
			sprite->y = (int)sprite->current_Vy;
		}
		else
		{
			sprite->x = (int)(sprite->current_Vx + 0.000001);
			sprite->y = (int)sprite->current_Vy;
		}
	}
	return (1);
}

void	sprite_draw(t_map *map, float raylen, float raydir)
{
	t_sprite	sprite;

	raydir = modulo_perso(raydir - 1, 4);
	raydir = - ft_map_values_f(raydir, 4, 2 * M_PI);
	raydir = modulo_perso(raydir, 2 * M_PI);
	sprite.Vx = map->player.x + raylen * cos(raydir);
	sprite.Vy = map->player.y - raylen * sin(raydir);
	sprite.Hx = sprite.Vx;
	sprite.Hy = sprite.Vy;
	sprite.start_x = sprite.Vx;
	sprite.start_y = sprite.Vy;
	if (raydir >= 0 && raydir <= M_PI)
	{
		sprite.Hx += (sprite.Hy - (int)sprite.Hy) / tan(raydir);
		sprite.Hy = (int)sprite.Hy;
	}
	else
	{
		sprite.Hx -= (1 - sprite.Hy + (int)sprite.Hy) / tan(raydir);
		sprite.Hy = (int)sprite.Hy + 1;
	}
	if (raydir >= M_PI_2 && raydir <= 3 * M_PI_2)
	{
		sprite.Vy += (sprite.Vx - (int)sprite.Vx) * tan(raydir);
		sprite.Vx = (int)sprite.Vx;
	}
	else
	{
		sprite.Vy -= (1 - sprite.Vx + (int)sprite.Vx) * tan(raydir);
		sprite.Vx = (int)sprite.Vx + 1;
	}
	sprite.current_Vx = sprite.Vx;
	sprite.current_Vy = sprite.Vy;
	sprite.current_Hx = sprite.Hx;
	sprite.current_Hy = sprite.Hy;
	while (next_sprite(&sprite, map, raylen, modulo_perso(raydir - M_PI, 2 * M_PI)) > 0)
		put_sprite(&sprite, map, raydir);
}