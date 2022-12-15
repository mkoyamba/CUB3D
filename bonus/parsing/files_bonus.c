/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:41:20 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/14 12:24:03 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/parsing_bonus.h"

void	free_textures_xpm(t_map *map)
{
	int	n;

	n = 0;
	while (n < 12)
	{
		if (map->img[n].ptr)
			mlx_destroy_image(map->vars.mlx, map->img[n].ptr);
		n++;
	}
}

int	textures_init_xpm(t_map *map)
{
	int	n;

	n = 0;
	while (n < 12)
	{
		map->img[n].ptr = mlx_xpm_file_to_image(map->vars.mlx, map->textures[n],
						&(map->img[n].x), &(map->img[n].y));
		if (!map->img[n].ptr)
		{
			ft_putstr_fd("Error\ncub3d: No such texture file: ", 2);
			ft_putendl_fd(map->textures[n], 2);
			free_struct_map(map);
			return (0);
		}
		n++;
	}
	return (1);
}