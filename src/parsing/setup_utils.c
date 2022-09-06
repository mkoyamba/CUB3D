/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:58:03 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 12:57:45 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	get_colors_parsing(char *line, t_map *map, char c)
{
	char	**colors;

	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (0);
	colors = ft_split(line, ',');
	if (!colors)
		return (0);
	if (c == 'f')
	{
		map->floor[0] = ft_atoi(colors[0]);
		map->floor[1] = ft_atoi(colors[1]);
		map->floor[2] = ft_atoi(colors[2]);
	}
	else
	{
		map->ceiling[0] = ft_atoi(colors[0]);
		map->ceiling[1] = ft_atoi(colors[1]);
		map->ceiling[2] = ft_atoi(colors[2]);
	}
	free_mat(colors);
	return (1);
}

int	get_textures_parsing(t_map *map, char **readed)
{
	char	*text[5];
	int		n;

	text[NORTH] = line_pos(readed, "NO ") + 2;
	text[SOUTH] = line_pos(readed, "SO ") + 2;
	text[WEST] = line_pos(readed, "WE ") + 2;
	text[EAST] = line_pos(readed, "EA ") + 2;
	text[4] = NULL;
	n = 0;
	while (text[n])
	{
		while (*text[n] && *text[n] == ' ')
			text[n]++;
		if (ft_strncmp(text[n], "./", 2))
			return (0);
		map->textures[n] = ft_strdup(text[n]);
		if (!map->textures[n])
			return (0);
		if (map->textures[n][ft_strlen(map->textures[n]) - 1] == '\n')
			map->textures[n][ft_strlen(map->textures[n]) - 1] = '\0';
		n++;
	}
	return (1);
}
