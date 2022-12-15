/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:22:55 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/14 16:52:24 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

int	is_in_map(float x, float y, t_map *map)
{
	if (x < 0 || y < 0
		|| (int)x < 0 || (int)y < 0
		|| y >= matlen(map->map) || x >= ft_strlen(map->map[(int)y])
		|| map->map[(int)y][(int)x] == ' ')
		return (0);
	return (1);
}

int	ft_map_values(float value, float from, float to)
{
	return(value / from * to);
}

float	ft_map_values_f(float value, float from, float to)
{
	return(value / from * to);
}

int	is_valid_pos(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '0' && map->map[(int)y][(int)x] != '4')
		return (0);
	else if (map->map[(int)y][(int)x] != '4')
		return (2);
	return (1);
}

int	is_wall(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '1')
		return (0);
	return (1);
}

int	is_door(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '2' && map->map[(int)y][(int)x] != '3')
		return (0);
	return (1);
}

int	is_valid_pos_player(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '0'
		&& map->map[(int)y][(int)x] != '3'
		&& map->map[(int)y][(int)x] != '4')
		return (0);
	return (1);
}
