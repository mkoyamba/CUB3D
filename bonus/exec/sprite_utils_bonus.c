/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:42:59 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:06:06 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	next_sprite_h(t_sprite *sprite, float raydir)
{
	sprite->vx = sprite->current_vx;
	sprite->vy = sprite->current_vy;
	sprite->current_hx = sprite->hx;
	sprite->current_hy = sprite->hy;
	if (raydir >= 0 && raydir < M_PI)
	{
		sprite->x = (int)sprite->current_hx;
		sprite->y = (int)(sprite->current_hy - 0.000001);
	}
	else
	{
		sprite->x = (int)sprite->current_hx;
		sprite->y = (int)(sprite->current_hy + 0.000001);
	}
}

void	next_sprite_v(t_sprite *sprite, float raydir)
{
	sprite->hx = sprite->current_hx;
	sprite->hy = sprite->current_hy;
	sprite->current_vx = sprite->vx;
	sprite->current_vy = sprite->vy;
	if (raydir >= M_PI_2 && raydir < 3 * M_PI_2)
	{
		sprite->x = (int)(sprite->current_vx - 0.000001);
		sprite->y = (int)sprite->current_vy;
	}
	else
	{
		sprite->x = (int)(sprite->current_vx + 0.000001);
		sprite->y = (int)sprite->current_vy;
	}
}

int	next_sprite(t_sprite *sprite, t_map *map, float raylen, float raydir)
{
	int	state_h;
	int	state_v;

	state_h = new_sprite_pos(raydir, sprite, HORIZONTAL, map);
	state_v = new_sprite_pos(raydir, sprite, VERTICAL, map);
	while (!state_h)
		state_h = new_sprite_pos(raydir, sprite, HORIZONTAL, map);
	while (!state_v)
		state_v = new_sprite_pos(raydir, sprite, VERTICAL, map);
	sprite->h_raylen = sqrtf(powf(sprite->start_x - sprite->hx, 2)
			+ powf(sprite->start_y - sprite->hy, 2));
	sprite->v_raylen = sqrtf(powf(sprite->start_x - sprite->vx, 2)
			+ powf(sprite->start_y - sprite->vy, 2));
	if ((state_h != 1 && state_v != 1)
		|| (sprite->h_raylen > raylen && sprite->v_raylen > raylen))
	{
		return (0);
	}
	if ((state_v == -1) || (sprite->h_raylen > 0
			&& (sprite->h_raylen < sprite->v_raylen || sprite->v_raylen < 0)))
		next_sprite_h(sprite, raydir);
	else
		next_sprite_v(sprite, raydir);
	return (1);
}

void	sprite_draw_utils(
	t_map *map, float raylen, float *raydir, t_sprite *sprite)
{
	*raydir = modulo_perso(*raydir - 1, 4);
	*raydir = -ft_map_values_f(*raydir, 4, 2 * M_PI);
	*raydir = modulo_perso(*raydir, 2 * M_PI);
	sprite->vx = map->player.x + raylen * cos(*raydir);
	sprite->vy = map->player.y - raylen * sin(*raydir);
	sprite->hx = sprite->vx;
	sprite->hy = sprite->vy;
	sprite->start_x = sprite->vx;
	sprite->start_y = sprite->vy;
	if (*raydir >= 0 && *raydir <= M_PI)
	{
		sprite->hx += (sprite->hy - (int)sprite->hy) / tan(*raydir);
		sprite->hy = (int)sprite->hy;
		sprite->hx += 0.2 / tan(*raydir);
		sprite->hy -= 0.2;
	}
	else
	{
		sprite->hx -= (1 - sprite->hy + (int)sprite->hy) / tan(*raydir);
		sprite->hy = (int)sprite->hy + 1;
		sprite->hx -= 0.2 / tan(*raydir);
		sprite->hy += 0.2;
	}
}

void	sprite_draw(t_map *map, float raylen, float raydir)
{
	t_sprite	sprite;

	sprite_draw_utils(map, raylen, &raydir, &sprite);
	if (raydir >= M_PI_2 && raydir <= 3 * M_PI_2)
	{
		sprite.vy += (sprite.vx - (int)sprite.vx) * tan(raydir);
		sprite.vx = (int)sprite.vx;
		sprite.vy += 0.2 * tan(raydir);
		sprite.vx -= 0.2;
	}
	else
	{
		sprite.vy -= (1 - sprite.vx + (int)sprite.vx) * tan(raydir);
		sprite.vx = (int)sprite.vx + 1;
		sprite.vx += 0.2;
		sprite.vy -= 0.2 * tan(raydir);
	}
	sprite.current_vx = sprite.vx;
	sprite.current_vy = sprite.vy;
	sprite.current_hx = sprite.hx;
	sprite.current_hy = sprite.hy;
	while (next_sprite(&sprite, map, raylen,
			modulo_perso(raydir - M_PI, 2 * M_PI)) > 0)
		put_sprite(&sprite, map, raydir);
}
