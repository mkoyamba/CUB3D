/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:11:37 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/09 15:34:33 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/parsing_bonus.h"

static void	set_struct(t_map *map, char **readed)
{
	int	n;

	n = 0;
	set_map_struct(map, readed);
	while (map->map[n])
	{
		if (map->map[n][ft_strlen(map->map[n]) - 1] == '\n')
			map->map[n][ft_strlen(map->map[n]) - 1] = '\0';
		n++;
	}
	if (!set_map_infos(map, readed))
	{
		free_struct_map(map);
		free_mat(readed);
		error_out(E_MALLOC, 1);
	}
	free_mat(readed);
}

static char	*check_syntax(char **readed)
{
	if (!check_path(readed))
		return (E_PARAM);
	if (!check_colors(readed))
		return (E_COLORS);
	if (!check_map_pos(readed))
		return (E_MAP_POS);
	return (NULL);
}

static t_map	*get_struct(int fd)
{
	t_map	*result;
	char	**readed;
	char	*syntax;

	result = malloc(sizeof(t_map));
	if (!result)
	{
		close(fd);
		error_out(E_MALLOC, 1);
	}
	init_struct_map(result);
	readed = read_map(fd);
	syntax = check_syntax(readed);
	if (!readed || syntax)
	{
		close(fd);
		free_struct_map(result);
		if (!readed)
			error_out(E_MALLOC, 1);
		free_mat(readed);
		error_out(syntax, 1);
	}
	close(fd);
	set_struct(result, readed);
	return (result);
}

t_map	*parsing(int argc, char **argv)
{
	int	fd;

	if (argc != 2 || ft_strlen(argv[1]) < 4)
		error_out(E_ARGS, 1);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 4))
	{
		ft_putstr_fd("Error\ncub3d: ", STDERR);
		ft_putendl_fd(E_FORMAT, STDERR);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\ncub3d: ", STDERR);
		ft_putstr_fd(argv[1], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(E_FILE, STDERR);
		exit(1);
	}
	return (get_struct(fd));
}
