/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:30:08 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 18:52:36 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

int	is_valid_pos(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] != '0')
		return (0);
	return (1);
}

float	modulo_perso(float result, float modulo)
{
	if (result < 0)
		result = modulo + result;
	if (result >= modulo)
		result = result - modulo;
	return (result);
}
