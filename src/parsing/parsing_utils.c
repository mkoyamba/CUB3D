/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:34:18 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/07 19:08:00 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

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
	map->map = NULL;
	map->vars.mlx = NULL;
	map->vars.win = NULL;
	map->img[NORTH].ptr = NULL;
	map->img[SOUTH].ptr = NULL;
	map->img[EAST].ptr = NULL;
	map->img[WEST].ptr = NULL;
	map->textures[NORTH] = NULL;
	map->textures[SOUTH] = NULL;
	map->textures[EAST] = NULL;
	map->textures[WEST] = NULL;
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
