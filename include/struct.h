/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 15:32:16 by mkoyamba         ###   ########.fr       */
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
	int	height;
	int	start;
}				t_column;

typedef struct s_map
{
	t_vars		vars;
	t_player	player;
	t_column	column;
	char		**map;
	char		*textures[4];
	t_img		img[4];
	int			floor;
	int			ceiling;
	int			refresh;
	char		*buffer;
	int			pixel_bits;
	int			line_bytes;
	int			wall_color;
	float		wall_pos;
	int			endian;
	float		ray_len_v;
	float		ray_len_h;
}				t_map;

#endif