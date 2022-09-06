/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:31:15 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 11:54:17 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	check_path(char **readed)
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	no = line_pos(readed, "NO ");
	so = line_pos(readed, "SO ");
	we = line_pos(readed, "WE ");
	ea = line_pos(readed, "EA ");
	if (!no || !so || !we || !ea)
		return (0);
	else
		return (1);
}

static int	check_digit(char **colors)
{
	int	n;
	int	i;

	i = 0;
	while (colors[i])
	{
		n = 0;
		while (colors[i][n])
		{
			if (!ft_isdigit(colors[i][n]) && colors[i][n] != '\n')
			{
				free_mat(colors);
				return (0);
			}
			n++;
		}
		i++;
	}
	return (1);
}

static int	syntax_check_colors(char *line)
{
	char	**colors;

	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (0);
	colors = ft_split(line, ',');
	if (!colors || matlen(colors) != 3)
	{
		if (colors)
			free(colors);
		return (0);
	}
	if (!check_digit(colors) || !check_values(colors))
		return (0);
	free_mat(colors);
	return (1);
}

int	check_colors(char **readed)
{
	char	*ceil_line;
	char	*floor_line;

	ceil_line = line_pos(readed, "C ");
	floor_line = line_pos(readed, "F ");
	if (!ceil_line || !floor_line)
		return (0);
	if (!syntax_check_colors(floor_line + 1))
		return (0);
	if (!syntax_check_colors(ceil_line + 1))
		return (0);
	return (1);
}

int	check_map_pos(char **readed)
{
	int	i;

	i = matlen(readed) - 1;
	if (!valid_line_map(readed[i]))
		return (0);
	while (i >= 0 && valid_line_map(readed[i]))
		i--;
	while (i >= 0)
	{
		if (ft_strncmp(readed[i], "NO ", 3) && ft_strncmp(readed[i], "SO ", 3)
			&& ft_strncmp(readed[i], "WE ", 3)
			&& ft_strncmp(readed[i], "EA ", 3) && ft_strncmp(readed[i], "F ", 2)
			&& ft_strncmp(readed[i], "C ", 2) && ft_strncmp(readed[i], "\n", 1))
			return (0);
		i--;
	}
	return (1);
}
