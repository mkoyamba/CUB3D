/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:03:15 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:08:16 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d_bonus.h"

//          ----------========== {     FCTS     } ==========----------

int		game_loop(t_map *map);
void	refresh_screen(t_map *map);
int		end_exec(t_map *map);
void	event_left_arrow(t_map *map);
void	event_right_arrow(t_map *map);
void	event_w(t_map *map);
void	event_s(t_map *map);
void	event_a(t_map *map);
void	event_d(t_map *map);
int		mouse_move(int x, int y, t_map *map);
int		event_key_pressed(int keycode, t_map *map);
int		event_key_released(int keycode, t_map *map);
int		is_valid_pos(t_map *map, float x, float y);
int		is_valid_pos_player(t_map *map, float x, float y);
int		is_wall(t_map *map, float x, float y);
int		is_door(t_map *map, float x, float y);
int		is_coin(t_map *map, float x, float y);
float	new_pos_x(t_map *map);
float	new_pos_y(t_map *map);
void	manahge_door(t_map *map);
float	modulo_perso(float result, float modulo);
void	raycast(int n, t_map *map, float raydir);
float	ray_split_se(t_map *map, float raydir, float *x, float *y);
float	return_check_se(t_map *map, float raydir, float *x, float *y);
float	ray_split_sw(t_map *map, float raydir, float *x, float *y);
float	return_check_sw(t_map *map, float raydir, float *x, float *y);
float	ray_split_ne(t_map *map, float raydir, float *x, float *y);
float	return_check_ne(t_map *map, float raydir, float *x, float *y);
float	ray_split_nw(t_map *map, float raydir, float *x, float *y);
float	return_check_nw(t_map *map, float raydir, float *x, float *y);
int		is_in_map(float x, float y, t_map *map);
float	get_move_dir(t_map *map);
float	new_colision_x(t_map *map);
float	new_colision_y(t_map *map);
void	put_pixel(int x, int y, int color, t_map *map);
int		ft_map_values(float value, float from, float to);
float	ft_map_values_f(float value, float from, float to);
int		switch_color(int color);
void	sprite_draw(t_map *map, float raylen, float raydir);
int		new_sprite_pos(float raydir, t_sprite *sprite, int mode, t_map *map);
void	get_coin(t_map *map);
void	put_coins(t_map *map);
void	put_coin_img(t_map *map);
void	put_coin_obtained(t_map *map);
void	manahge_door_utils(t_map *map, float dir);
void	put_sprite(t_sprite *sprite, t_map *map, float raydir);
void	wall_color_img(t_map *map, char **img);
void	raycast_utils(t_map *map, int middle_part, float raylen, float raydir);
void	set_wall_color(t_map *map, int n, int i);
void	put_big_minimap(t_map *map);
void	put_minimap(t_map *map);
void	put_crosshair(t_map *map);
void	print_coin_obtained(t_map *map, char *img, int n);

#endif