/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/10 17:16:14 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d_bonus.h"

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
	int		pos_turn;
	int		open;
}				t_player;

typedef struct s_img
{
	void	*ptr;
	int		endian;
	int		size_line;
	int		bits_pixel;
	int		x;
	int		y;
}				t_img;

typedef struct s_column
{
	int		height;
	int		start;
	char	typeV;
	char	typeH;
	char	type;
	float	raylen;
}				t_column;

typedef struct s_map
{
	t_vars		vars;
	t_player	player;
	t_column	column;
	char		**map;
	char		*textures[11];
	t_img		img[11];
	int			floor;
	int			ceiling;
	int			refresh;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			wall_color;
	float		wall_pos;
	int			endian;
	int			minimap;
	float		anim;
}				t_map;

#endif