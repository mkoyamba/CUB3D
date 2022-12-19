/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:53:32 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/12/19 19:07:43 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	error_out(char *str, int code)
{
	ft_putstr_fd("Error\ncub3d: ", STDERR);
	ft_putendl_fd(str, STDERR);
	exit(code);
}

int	new_game(t_map *map)
{
	map->vars.mlx = mlx_init();
	if (!textures_init_xpm(map))
		return (1);
	map->vars.win = mlx_new_window(
			map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_mouse_move(map->vars.win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_mouse_hide();
	mlx_hook(map->vars.win, 17, 0, end_exec, map);
	mlx_hook(map->vars.win, 2, 0, event_key_pressed, map);
	mlx_hook(map->vars.win, 3, 0, event_key_released, map);
	mlx_hook(map->vars.win, 6, 0, mouse_move, map);
	map->vars.screen = mlx_new_image(
			map->vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	map->buffer = mlx_get_data_addr(map->vars.screen,
			&(map->pixel_bits), &(map->line_bytes), &(map->endian));
	mlx_loop_hook(map->vars.mlx, game_loop, map);
	mlx_loop(map->vars.mlx);
	return (0);
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
