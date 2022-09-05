/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:25 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 14:10:16 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d.h"

//          ----------========== {   STRUCTS    } ==========----------

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
}				t_player;

typedef struct s_map
{
	char		**map;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_player	player;
	int			ground[3];
	int			ceiling[3];
}				t_map;

#endif