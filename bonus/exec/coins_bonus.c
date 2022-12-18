/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coins_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 12:06:22 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/18 13:43:17 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

/*void	put_coin_obtained(t_map *map)
{
	
}*/

void	put_coin_img(t_map *map)
{
	int		n;
	int		i;
	char	*img;
	int		color;

	n = 0;
	img = mlx_get_data_addr (map->img[(int)map->anim + BIG_COIN].ptr,
			&(map->img[(int)map->anim + BIG_COIN].bits_pixel),
			&(map->img[(int)map->anim + BIG_COIN].size_line),
			&(map->img[(int)map->anim + BIG_COIN].endian));
	while (n < 32)
	{
		i = 0;
		while (i < 32)
		{
			color = *(int *)(img
			+ (4 * (map->img[(int)map->anim + BIG_COIN].x) * ft_map_values(i, 32, map->img[(int)map->anim + BIG_COIN].y))
			+ (4 * ft_map_values(n, 32, map->img[(int)map->anim + BIG_COIN].x)));
			if (color == (int)EMPTY_COLOR)
			{
				i++;
				continue ;
			}
			if (!map->img[(int)map->anim + BIG_COIN].endian)
				put_pixel(SCREEN_WIDTH - 42 + n, 10 + i, switch_color(color), map);
			else
				put_pixel(SCREEN_WIDTH - 42 + n, 10 + i, color, map);
			i++;
		}
		n++;
	}
}

void	put_coins(t_map *map)
{
	char	*number;

	number = ft_itoa(map->coins);
	if (!number)
		return ;
	mlx_string_put (map->vars.mlx, map->vars.win,
		SCREEN_WIDTH - (ft_strlen(number) * 7 + 50), 30, 0x00000000, number);
	free(number);
}

void	get_coin(t_map *map)
{
	if (map->map[(int)map->player.y][(int)map->player.x] == '4')
	{
		map->coins++;
		map->got_coin = 0;
		map->map[(int)map->player.y][(int)map->player.x] = '0';
	}
	if (map->got_coin < 5)
		map->got_coin += ANIM_SPEED;
	else
		map->got_coin = 0;
}