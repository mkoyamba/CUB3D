/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:04:15 by mkoyamba          #+#    #+#             */
/*   Updated: 2022/09/05 20:06:34 by mkoyamba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//          ----------========== {   INCLUDES   } ==========----------

# include "cub3d.h"

//          ----------========== {     FCTS     } ==========----------

void	free_mat(char **tab);
int		matlen(char **tab);
t_map	*parsing(int argc, char **argv);
void	free_struct_map(t_map *map);
void	init_struct_map(t_map *map);
char	**read_map(int fd);
char	**split_cub3d(char const *s, char c);
int		check_values(char **colors);
int		valid_line_map(char *line);
char	*line_pos(char **readed, char *str);
int		check_map_pos(char **readed);
int		check_colors(char **readed);
int		check_path(char **readed);
char	*check_map(char **map);
void	set_map_struct(t_map *map, readed);
char	**matdup(char **mat);

#endif