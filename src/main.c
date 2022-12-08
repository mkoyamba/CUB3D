/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:53:32 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/07 19:12:51 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	result = new_game(map);
	return (result);
}
