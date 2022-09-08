/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:03:15 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 17:14:25 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d.h"

//          ----------========== {     FCTS     } ==========----------

int		new_game(t_map *map);
int		end_exec(t_map *map);
void	event_left_arrow(t_map *map);
void	event_right_arrow(t_map *map);
void	event_w(t_map *map);
void	event_s(t_map *map);
void	event_a(t_map *map);
void	event_d(t_map *map);
int		event_key_pressed(int keycode, t_map *map);
int		event_key_released(int keycode, t_map *map);
int		is_valid_pos(t_map *map, float x, float y);
float	new_pos_x(t_map *map);
float	new_pos_y(t_map *map);
float	modulo_perso(float result, float modulo);
void	raycast(int n, t_map *map, float raydir);
float	get_move_dir(t_map *map);
float	new_colision_x(t_map *map);
float	new_colision_y(t_map *map);
void	put_pixel(int x, int y, int color, t_map *map);
void	get_wall_color(t_map *map, float raydir);

#endif