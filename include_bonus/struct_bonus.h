/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 18:33:21 by mkoyamba         ###   ########.fr       */
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
	char	typev;
	char	typeh;
	char	type;
	float	raylen;
	int		is_sprite;
	int		n;
	int		first_sprite;
}				t_column;

typedef struct s_sprite
{
	float	current_hx;
	float	current_hy;
	float	hx;
	float	hy;
	float	current_vx;
	float	current_vy;
	float	vx;
	float	vy;
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
	char		*textures[19];
	t_img		img[19];
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
	float		got_coin;
	int			coins;
	float		ray_len_v;
	float		ray_len_h;
}				t_map;

#endif