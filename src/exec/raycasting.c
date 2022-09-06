/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:31:29 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/06 23:34:46 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

static void		ray_len_next(
			t_map *map, float raydir, float *new_pos_x, float *new_pos_y)
{
	while (raydir > 2 && raydir < 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * sin((raydir - 2) * M_PI_2);
		*new_pos_y += 0.01 * cos((raydir - 2) * M_PI_2);
	}
	while (raydir > 3 && is_valid_pos(map, *new_pos_x, *new_pos_y))
	{
		*new_pos_x -= 0.01 * cos((raydir - 3) * M_PI_2);
		*new_pos_y -= 0.01 * sin((raydir - 3) * M_PI_2);
	}
}

static float	ray_len(t_map *map, float raydir)
{
	float	new_pos_x;
	float	new_pos_y;
	float	len;

	new_pos_x = map->player.x;
	new_pos_y = map->player.y;
	while (raydir > 0 && raydir < 1 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * sin(raydir * M_PI_2);
		new_pos_y -= 0.01 * cos(raydir * M_PI_2);
	}
	while (raydir > 1 && raydir < 2 && is_valid_pos(map, new_pos_x, new_pos_y))
	{
		new_pos_x += 0.01 * cos((raydir - 1) * M_PI_2);
		new_pos_y += 0.01 * sin((raydir - 1) * M_PI_2);
	}
	ray_len_next(map, raydir, &new_pos_x, &new_pos_y);
	len = sqrtf(powf(map->player.x - new_pos_x, 2) + 
		powf(map->player.y - new_pos_y, 2));
	return (len);
}

/*static void set_new_pos_intersection(
	t_map *map, float raydir, float *new_pos_x, float *new_pos_y)
{
	float	len;

	len = ray_len(map, raydir);
	if (raydir >= NORTH && raydir < EAST)
	{
		*new_pos_x = map->player.x + len * sin(raydir * M_PI_2);
		*new_pos_y = map->player.y - len * cos(raydir * M_PI_2);
	}
	else if (raydir >= EAST && raydir < SOUTH)
	{
		*new_pos_x = map->player.x + len * cos((raydir - 1) * M_PI_2);
		*new_pos_y = map->player.y + len * sin((raydir - 1) * M_PI_2);
	}
	else if (raydir >= SOUTH && raydir < WEST)
	{
		*new_pos_x = map->player.x - len * sin((raydir - 2) * M_PI_2);
		*new_pos_y = map->player.y + len * cos((raydir - 2) * M_PI_2);
	}
	else
	{
		*new_pos_x = map->player.x - len * cos((raydir - 3) * M_PI_2);
		*new_pos_y = map->player.y - len * sin((raydir - 3) * M_PI_2);
	}
}*/

void	raycast(int n, t_map *map, float raydir)
{
	float	len_ray;
	int		middle_part;
//	float	new_pos_x;
//	float	new_pos_y;
	char	*buffer;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	int		pixel;
	int		i;

	if (raydir - (int)raydir == 0)
		raydir += 0.00001;
	len_ray = ray_len(map, raydir);
	middle_part = (int)((CUBE_SIZE * 900)/len_ray);
	buffer = mlx_get_data_addr(map->vars.screen, &pixel_bits, &line_bytes, &endian);
	i = 0;
	while (i < 450 - middle_part/2)
	{
		pixel = (i * line_bytes) + (n * 4);
		buffer[pixel + 0] = (unsigned char)0;
		buffer[pixel + 1] = (unsigned char)225;
		buffer[pixel + 2] = (unsigned char)30;
		buffer[pixel + 3] = (unsigned char)0;
		i++;
	}
	while (i < 450 + middle_part/2)
	{
		pixel = (i * line_bytes) + (n * 4);
		buffer[pixel + 0] = (unsigned char)0;
		buffer[pixel + 1] = (unsigned char)100;
		buffer[pixel + 2] = (unsigned char)100;
		buffer[pixel + 3] = (unsigned char)100;
		i++;
	}
	while (i < 900)
	{
		pixel = (i * line_bytes) + (n * 4);
		buffer[pixel + 0] = (unsigned char)0;
		buffer[pixel + 1] = (unsigned char)220;
		buffer[pixel + 2] = (unsigned char)100;
		buffer[pixel + 3] = (unsigned char)0;
		i++;
	}
	mlx_put_image_to_window(map->vars.mlx, map->vars.win, map->vars.screen, 0, 0);
	//set_new_pos_intersection(map, raydir, &new_pos_x,&new_pos_y);
	
}