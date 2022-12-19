/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_crosshair_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:28:58 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:08:48 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/exec_bonus.h"

static void	put_crosshair_deux(t_map *map)
{
	int	n;
	int	i;

	n = 0;
	while (n < 2)
	{
		i = 0;
		while (i < CROSSHAIR_SIZE * 2 - 1)
		{
			put_pixel(SCREEN_WIDTH / 2 - 1 + n,
				SCREEN_HEIGHT / 2 - CROSSHAIR_SIZE + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
}

void	put_crosshair(t_map *map)
{
	int	n;
	int	i;

	n = 0;
	while (n < CROSSHAIR_SIZE * 2 - 2)
	{
		i = 0;
		while (i < 3)
		{
			put_pixel(SCREEN_WIDTH / 2 - CROSSHAIR_SIZE + 1 + n,
				SCREEN_HEIGHT / 2 - 2 + i, CROSSHAIR_COLOR, map);
			i++;
		}
		n++;
	}
	put_crosshair_deux(map);
}
