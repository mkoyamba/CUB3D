/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:03:15 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/10 15:41:52 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d_bonus.h"

//          ----------========== {     FCTS     } ==========----------

int		new_game(t_map *map);
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
float	new_pos_x(t_map *map);
float	new_pos_y(t_map *map);
void	manahge_door(t_map *map);
float	modulo_perso(float result, float modulo);
void	raycast(int n, t_map *map, float raydir);
float	ray_split_se(t_map *map, float raydir, float *x, float *y);
float	ray_split_sw(t_map *map, float raydir, float *x, float *y);
float	ray_split_ne(t_map *map, float raydir, float *x, float *y);
float	ray_split_nw(t_map *map, float raydir, float *x, float *y);
int		is_in_map(float x, float y, t_map *map);
float	get_move_dir(t_map *map);
float	new_colision_x(t_map *map);
float	new_colision_y(t_map *map);
void	put_pixel(int x, int y, int color, t_map *map);
int		ft_map_values(float value, float from, float to);
float	ft_map_values_f(float value, float from, float to);

#endif