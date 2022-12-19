/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:58:03 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 14:54:14 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static void	set_int_color(int *result, char **colors)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	*buf;

	r = (unsigned char)ft_atoi(colors[0]);
	g = (unsigned char)ft_atoi(colors[1]);
	b = (unsigned char)ft_atoi(colors[2]);
	buf = (unsigned char *)result;
	buf[0] = 255;
	buf[1] = r;
	buf[2] = g;
	buf[3] = b;
}

int	get_colors_parsing(char *line, t_map *map, char c)
{
	char			**colors;

	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (0);
	colors = ft_split(line, ',');
	if (!colors)
		return (0);
	if (c == 'f')
		set_int_color(&(map->floor), colors);
	else
		set_int_color(&(map->ceiling), colors);
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
