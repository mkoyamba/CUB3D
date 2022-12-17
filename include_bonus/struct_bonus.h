/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/17 12:22:38 by mkoyamba         ###   ########.fr       */
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
	int		is_sprite;
	int		n;
}				t_column;

typedef struct s_sprite
{
	float	current_Hx;
	float	current_Hy;
	float	Hx;
	float	Hy;
	float	current_Vx;
	float	current_Vy;
	float	Vx;
	float	Vy;
	float	start_x;
	float	start_y;
	float	h_raylen;
	float	v_raylen;
	float	raydir;
	int		x;
	int		y;
}				t_sprite;

typedef struct s_map
{
	t_vars		vars;
	t_player	player;
	t_column	column;
	char		**map;
	char		*textures[12];
	t_img		img[12];
	int			floor;
	int			ceiling;
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