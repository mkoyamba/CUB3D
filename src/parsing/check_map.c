/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bade-lee <bade-lee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 20:05:56 by mkoyamba          #+#    #+#             */
/*   Updated: 2023/01/09 10:10:39 by bade-lee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

static char	*check_zero(char **map, size_t n, size_t i)
{
	if (n == 0 || i == 0 || (int)n == matlen(map) - 1
		|| i == ft_strlen(map[n]) - 2 || map[n][i - 1] == ' '
		|| map[n][i + 1] == ' ')
		return (E_CLOSED_MAP);
	if (ft_strlen(map[n - 1]) < i + 2 || ft_strlen(map[n + 1]) < i + 2
		|| map[n - 1][i] == ' ' || map[n + 1][i] == ' ')
		return (E_CLOSED_MAP);
	if (map[n - 1][i - 1] == ' ' || map[n + 1][i + 1] == ' '
		|| map[n - 1][i + 1] == ' ' || map[n + 1][i - 1] == ' ')
		return (E_CLOSED_MAP);
	if (map[n - 1][i - 1] == '\n' || map[n + 1][i + 1] == '\n'
		|| map[n - 1][i + 1] == '\n' || map[n + 1][i - 1] == '\n')
		return (E_CLOSED_MAP);
	return (NULL);
}

char	*check_map(char **map)
{
	size_t	n;
	size_t	i;

	n = 0;
	while (map[n])
	{
		i = 0;
		while (map[n][i])
		{
			if (map[n][i] == '0' && check_zero(map, n, i))
				return (check_zero(map, n, i));
			i++;
		}
		n++;
	}
	return (NULL);
}
