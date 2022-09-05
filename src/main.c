/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:53:32 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 14:32:45 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	int		result;

	map = parsing(argc, argv);
	result = new_game(map);
	return (result);
}
