/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:53:32 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/10 17:35:37 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

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

	if (SCREEN_WIDTH < 250 || SCREEN_HEIGHT < 250)
		error_out(E_MAP_SIZE, 1);
	map = parsing(argc, argv);
	result = new_game(map);
	return (result);
}
