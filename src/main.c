/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:53:32 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 13:06:36 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map_test(t_map *map)
{
	int		n;
	char	*dir[4] = {"   NORTH = ", "   EAST = ", "   SOUTH = ", "   WEST = "};

	n = -1;
	ft_putendl_fd("\n\n                 MAP\n\n          ==================\n", 1);
	while (map->map[++n])
	{
		ft_putstr_fd("   ", 2);
		ft_putendl_fd(map->map[n], 2);
	}
	ft_putstr_fd("\n", 2);
	n = -1;
	ft_putendl_fd("               TEXTURES\n\n          ==================\n", 1);
	while (++n < 4)
	{
		ft_putstr_fd(dir[n], 2);
		ft_putendl_fd(map->textures[n], 2);
	}
	ft_putstr_fd("\n", 2);
	ft_putendl_fd("                PLAYER\n\n          ==================\n", 1);
	ft_putstr_fd("   Position x : ", 1);
	printf("%f\n", map->player.x);
	ft_putstr_fd("   Position y : ", 1);
	printf("%f\n", map->player.y);
	ft_putstr_fd("   Direction : ", 1);
	printf("%f\n", map->player.dir);
	n = -1;
	ft_putendl_fd("\n                COLORS\n\n          ==================\n", 1);
	ft_putstr_fd("   FLOOR : ", 2);
	while (++n < 3)
	{
		ft_putnbr_fd(map->floor[n], 2);
		ft_putstr_fd(" ", 2);
	}
	n = -1;
	ft_putstr_fd("\n   CEILING : ", 2);
	while (++n < 3)
	{
		ft_putnbr_fd(map->ceiling[n], 2);
		ft_putstr_fd(" ", 2);
	}
	ft_putstr_fd("\n\n", 2);
}

void	error_out(char *str, int code)
{
	ft_putstr_fd("Error\ncub3d: ", STDERR);
	ft_putendl_fd(str, STDERR);
	exit(code);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		result;

	map = parsing(argc, argv);
	//print_map_test(map);
	result = new_game(map);
	return (result);
}
