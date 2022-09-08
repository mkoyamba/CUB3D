/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/07 16:44:27 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d.h"

//          ----------========== {   STRUCTS    } ==========----------

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*screen;
}				t_vars;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
	int		right;
	int		left;
	int		forward;
	int		backward;
	int		trigo;
	int		antitrigo;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		*textures[4];
	t_player	player;
	int			floor;
	int			ceiling;
	t_vars		vars;
	int			refresh;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	int			wall_color;
}				t_map;

#endif