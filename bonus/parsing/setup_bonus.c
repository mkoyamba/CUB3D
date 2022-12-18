/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:51:23 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/18 13:02:51 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/parsing_bonus.h"

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

static void	set_player_start_postion(t_map *map, char *c, int i, int n)
{
	map->player.x = i + 0.5;
	map->player.y = n + 0.5;
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
	count = 0;
	while (map->map[n])
	{
		i = 0;
		while (map->map[n][i])
		{
			if (map->map[n][i] == 'N' || map->map[n][i] == 'E'
				|| map->map[n][i] == 'W' || map->map[n][i] == 'S')
			{
				set_player_start_postion(map, &(map->map[n][i]), i, n);
				count++;
			}
			i++;
		}
		n++;
	}
	if (count != 1)
		return (0);
	return (1);
}

void	set_map_struct(t_map *map, char **readed)
{
	int		i;
	char	*check_map_str;

	i = matlen(readed) - 1;
	while (i >= 0 && valid_line_map(readed[i]))
		i--;
	i++;
	map->map = matdup(&readed[i]);
	if (!map->map)
	{
		free_mat(readed);
		free_struct_map(map);
		error_out(E_MALLOC, 1);
	}
	check_map_str = check_map(map->map);
	if (!player_start_postion(map) || check_map_str)
	{
		free_mat(readed);
		free_struct_map(map);
		if (!check_map_str)
			error_out(E_PLAYER, 1);
		error_out(check_map_str, 1);
	}
}

int	set_map_infos(t_map *map, char **readed)
{
	char	*ceil_line;
	char	*floor_line;

	ceil_line = line_pos(readed, "C ");
	floor_line = line_pos(readed, "F ");
	if (!get_colors_parsing(floor_line + 1, map, 'f'))
		return (0);
	if (!get_colors_parsing(ceil_line + 1, map, 'c'))
		return (0);
	if (!get_textures_parsing(map, readed))
		return (0);
	return (1);
}
