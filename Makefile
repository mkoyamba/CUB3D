# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 12:29:55 by mkoyamba          #+#    #+#              #
#    Updated: 2022/09/06 22:07:05 by mkoyamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#          ----------========== {     VARS     } ==========----------

NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address
MLX_FLAGS = -framework OpenGL -framework AppKit
INCLUDE = -I include/cub3d.h
LIB = lib/libft/libft.a
MLX = lib/minilibx/libmlx.a

#          ----------========== {     SRCS     } ==========----------

SRC = main.c\

# parsing
SRC +=\
	parsing.c\
	parsing_utils.c\
	split_cub3d.c\
	syntax_check.c\
	syntax_utils.c\
	setup.c\
	check_map.c\
	setup_utils.c\

# exec
SRC +=\
	exec.c\
	exec_utils.c\
	events.c\
	events_utils.c\
	raycasting.c\

# files
SRC +=\
	files.c\

# animations
SRC +=\
	animations.c\

#          ----------========== {     OBJS     } ==========----------

SRC_DIR = src/
OBJ_DIR = src/obj_dir/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

VPATH= $(shell find $(SRC_DIR) -type d)

#          ----------========== {    REGLES    } ==========----------

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C lib/libft
	@make -sC lib/minilibx
	@$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJ) $(LIB) $(MLX) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@printf "\e[1;42m \e[0;m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C lib/libft clean
	@rm -f $(OBJ)
	@rm -rf obj_dir
	@printf "\e[0;31m[.o files deleted]\n\e[0;m"

fclean: clean
	@make -C lib/libft fclean
	@make -C lib/minilibx clean
	@rm -f $(NAME)
	@printf "\e[0;31m[cub3d deleted]\n\e[0;m"

re: fclean all

.PHONY: all clean fclean re