/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:52:06 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 20:25:56 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//          ----------========== {   INCLUDES   } ==========----------

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# include "../lib/minilibx/mlx.h"
# include "../lib/libft/include/libft.h"

# include "struct.h"
# include "animations.h"
# include "exec.h"
# include "files.h"
# include "menu.h"
# include "parsing.h"

//          ----------========== {     DEFS     } ==========----------

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

//parsing
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

//          ----------========== {     FCTS     } ==========----------

void	error_out(char *str, int code);

#endif