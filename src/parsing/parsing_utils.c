/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:34:18 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 19:47:10 by mkoyamba         ###   ########.fr       */
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
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->east)
		free(map->east);
	if (map->west)
		free(map->west);
	free(map);
}

void	init_struct_map(t_map *map)
{
	map->map = NULL;
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
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