/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:22:55 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/08 13:07:48 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

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
