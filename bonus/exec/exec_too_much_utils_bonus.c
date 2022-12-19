/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_too_much_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:01:30 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 17:57:17 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

void	manahge_door_utils(t_map *map, float dir)
{
	float	posx;
	float	posy;
	float	test_len_ray;

	test_len_ray = 0;
	posx = map->player.x;
	posy = map->player.y;
	while (test_len_ray < 2.5)
	{
		test_len_ray += 0.01;
		posx = sin(dir * M_PI * 2) * test_len_ray + map->player.x;
		posy = (-cos(dir * M_PI * 2)) * test_len_ray + map->player.y;
		if (map->map[(int)posy][(int)posx] == '3')
		{
			map->map[(int)posy][(int)posx] = '2';
			break ;
		}
		else if (map->map[(int)posy][(int)posx] == '2')
		{
			map->map[(int)posy][(int)posx] = '3';
			break ;
		}
	}
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

int	is_coin(t_map *map, float x, float y)
{
	if (map->map[(int)y][(int)x] == '4'
		&& sqrtf((powf(x - (int)x - 0.5, 2))
		+ (powf(y - (int)y - 0.5, 2))) < 0.2)
		return (1);
	return (0);
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
