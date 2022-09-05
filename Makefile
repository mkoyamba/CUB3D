# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 12:29:55 by mkoyamba          #+#    #+#              #
#    Updated: 2022/09/05 19:19:55 by mkoyamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#          ----------========== {     VARS     } ==========----------

NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address
#MLX_FLAGS = -framework OpenGL -framework AppKit
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

# exec
SRC +=\
	exec.c\

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
#	@make -C lib/minilibx
	@make -C lib/libft
	@$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
	@printf "\e[1;42m \e[0;m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C lib/libft clean
#	@make -C lib/minilibx clean
	@rm -f $(OBJ)
	@rm -rf obj_dir
	@printf "\e[0;31m[.o files deleted]\n\e[0;m"

fclean: clean
	@make -C lib/libft fclean
#	@make -C lib/minilibx fclean
	@rm -f $(NAME)
	@printf "\e[0;31m[cub3d deleted]\n\e[0;m"

re: fclean all

.PHONY: all clean fclean re