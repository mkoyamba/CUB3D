/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:53:56 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/09 19:13:24 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/parsing_bonus.h"

char	*line_pos(char **readed, char *str)
{
	char	*result;
	int		n;

	n = 0;
	result = NULL;
	while (readed[n])
	{
		if (!ft_strncmp(readed[n], str, ft_strlen(str)))
		{
			result = readed[n];
			break ;
		}
		n++;
	}
	if (!result)
		return (NULL);
	n++;
	while (readed[n])
	{
		if (!ft_strncmp(readed[n], str, ft_strlen(str)))
			return (NULL);
		n++;
	}
	return (result);
}

int	valid_line_map(char *line)
{
	int	n;

	n = 0;
	if (line[0] == '\n')
		return (0);
	while (line[n])
	{
		if (line[n] != ' ' && line[n] != '1' && line[n] != '0' && line[n] != 'N'
			&& line[n] != 'S' && line[n] != 'W' && line[n] != 'E'
			&& line[n] != '\n' && line[n] != '2' && line[n] != '3')
			return (0);
		n++;
	}
	return (1);
}

int	check_values(char **colors)
{
	int	values[3];

	values[0] = ft_atoi(colors[0]);
	values[1] = ft_atoi(colors[1]);
	values[2] = ft_atoi(colors[2]);
	if (values[0] < 0 || values[1] < 0 || values[2] < 0 || values[0] > 255
		|| values[1] > 255 || values[2] > 255)
	{
		free_mat(colors);
		return (0);
	}
	return (1);
}
