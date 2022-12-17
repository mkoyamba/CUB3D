/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:34:18 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/15 12:36:56 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/parsing_bonus.h"

int	matlen(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

void	free_mat(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
	{
		free(tab[n]);
		n++;
	}
	free(tab);
}

void	free_struct_map(t_map *map)
{
	if (map->map)
		free_mat(map->map);
	free_textures_xpm(map);
	if (map->textures[NORTH])
		free(map->textures[NORTH]);
	if (map->textures[SOUTH])
		free(map->textures[SOUTH]);
	if (map->textures[EAST])
		free(map->textures[EAST]);
	if (map->textures[WEST])
		free(map->textures[WEST]);
	if (map->vars.win)
		mlx_destroy_window(map->vars.mlx, map->vars.win);
	if (map->vars.mlx)
		free(map->vars.mlx);
	free(map);
}

void	init_struct_map(t_map *map)
{
	int	n;

	n = 0;
	while (n < 12)
	{
		map->img[n].ptr = NULL;
		map->textures[n] = NULL;
		n++;
	}
	map->map = NULL;
	map->vars.mlx = NULL;
	map->vars.win = NULL;
	map->player.right = 0;
	map->player.left = 0;
	map->player.forward = 0;
	map->player.backward = 0;
	map->player.trigo = 0;
	map->player.antitrigo = 0;
	map->player.x += 0.5;
	map->player.y += 0.5;
	map->player.pos_turn = 0;
	map->player.open = 0;
	map->minimap = 0;
	map->anim = 6;
	map->column.is_sprite = 0;
}

char	**read_map(int fd)
{
	char	*result;
	char	*trash;
	char	buf[10001];
	ssize_t	rd;
	char	**to_return;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	rd = 10000;
	while (rd == 10000)
	{
		rd = read(fd, buf, 10000);
		buf[rd] = '\0';
		trash = result;
		result = ft_strjoin(result, buf);
		free(trash);
	}
	to_return = split_cub3d(result, '\n');
	free(result);
	return (to_return);
}
