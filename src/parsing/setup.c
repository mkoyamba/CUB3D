/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:51:23 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 20:28:03 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	**matdup(char **mat)
{
	int		n;
	char	**result;

	n = 0;
	result = ft_calloc(matlen(mat) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (mat[n])
	{
		result[n] = ft_strdup(mat[n]);
		if (!result[n])
		{
			free_mat(result);
			return (NULL);
		}
		n++;
	}
	return (result);
}

static void	set_player_start_postion(t_map *map, char *c)
{
	if (*c == 'N')
		map->player.dir = NORTH;
	else if (*c == 'E')
		map->player.dir = EAST;
	else if (*c == 'S')
		map->player.dir = SOUTH;
	else if (*c == 'W')
		map->player.dir = WEST;
	*c = '0';
}

int	player_start_postion(t_map *map)
{
	int	n;
	int	i;
	int	count;

	n = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
		{
			if (map->map[n][i] == 'N' || map->map[n][i] == 'E'
				|| map->map[n][i] == 'W' || map->map[n][i] == 'S')
			{
				map->player.x = i;
				map->player.y = n;
				set_player_start_postion(map, &map[n][i]);
				count++;
			}
			i++;
		}
		n++;
	}
	if (count != 1)
		return (0)
	return (1);
}

void	set_map_struct(t_map *map, readed)
{
	int	i;

	i = matlen(readed) - 1;
	while (i >= 0 && valid_line_map(readed[i]))
		i--;
	i++;
	map->map = matdup(&readed[i]);
	if (!map->map)
	{
		mat_free(readed);
		free_struct_map(map);
		error_out(E_MALLOC, 1)
	}
	if (!player_start_postion(map) || check_map(map->map))
	{
		mat_free(readed);
		free_struct_map(map);
		if (!check_map(map->map))
			error_out(E_PLAYER, 1)
		error_out(check_map(map->map), 1)
	}
}