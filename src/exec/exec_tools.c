/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:22:55 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 15:18:07 by mkoyamba         ###   ########.fr       */
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

int	switch_color(int color)
{
	unsigned char	*color_buf;
	unsigned char	temp;

	color_buf = (unsigned char *)&color;
	temp = color_buf[3];
	color_buf[3] = color_buf[0];
	color_buf[0] = temp;
	temp = color_buf[1];
	color_buf[1] = color_buf[2];
	color_buf[2] = temp;
	return (color);
}

int	ft_map_values(float value, float from, float to)
{
	return (value / from * to);
}
