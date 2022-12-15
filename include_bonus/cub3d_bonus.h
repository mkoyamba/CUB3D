/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:52:06 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/14 15:13:39 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

//          ----------========== {   INCLUDES   } ==========----------

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include "../lib/minilibx/mlx.h"
# include "../lib/libft/include/libft.h"

# include "struct_bonus.h"
# include "exec_bonus.h"
# include "parsing_bonus.h"

//          ----------========== {     DEFS     } ==========----------

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3
# define CLOSED 4
# define OPENED 5
# define ANIM1 6
# define ANIM2 7
# define ANIM3 8
# define ANIM4 9
# define ANIM5 10
# define ANIM6 11

//path to textures
# define T_CLOSED "./textures/closed.xpm"
# define T_OPENED "./textures/opened.xpm"
# define T_ANIM1 "./textures/anim1.xpm"
# define T_ANIM2 "./textures/anim2.xpm"
# define T_ANIM3 "./textures/anim3.xpm"
# define T_ANIM4 "./textures/anim4.xpm"
# define T_ANIM5 "./textures/anim5.xpm"
# define T_ANIM6 "./textures/anim6.xpm"

//parsing
# define E_MAP_SIZE "screen needs to be at least 250x250"
# define E_ARGS "invalid arguments"
# define E_FORMAT "map must be formated as *.cub"
# define E_FILE "no such file"
# define E_MALLOC "memory allocation error"
# define E_PARAM "missing or extra textures"
# define E_PATH "bad textures path"
# define E_COLORS "missing or unvalid colors assignation"
# define E_MAP_POS "invalid file content"
# define E_MAP "invalid map content"
# define E_PLAYER "missing or extra player(s) on map"
# define E_CLOSED_MAP "the map is not closed"

//exec
# define SPEED 0.1
# define TURN_SPEED 0.03
# define CUBE_SIZE 1.8
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define COLLISION_LEN 0.25
# define CROSSHAIR_SIZE 8
# define CROSSHAIR_COLOR 0xDDDDDD00
# define ANIM_SPEED 0.2

//colors
# define EMPTY_COLOR 0xFFFFFF00

//          ----------========== {     FCTS     } ==========----------

void	error_out(char *str, int code);

#endif