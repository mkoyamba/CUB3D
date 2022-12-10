# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoyamba <mkoyamba@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 12:29:55 by mkoyamba          #+#    #+#              #
#    Updated: 2022/12/10 17:42:29 by mkoyamba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#          ----------========== {     VARS     } ==========----------

NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address
MLX_FLAGS = -framework OpenGL -framework AppKit
INCLUDE = -I include/cub3d.h
INCLUDE_B = -I include_bonus/cub3d_bonus.h
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
	files.c\

# exec
SRC +=\
	exec.c\
	exec_utils.c\
	exec_tools.c\
	events.c\
	events_utils.c\
	raycasting.c\
	raycasting_checks.c\

SRC_B = main_bonus.c\

# parsing
SRC_B +=\
	parsing_bonus.c\
	parsing_utils_bonus.c\
	split_cub3d_bonus.c\
	syntax_check_bonus.c\
	syntax_utils_bonus.c\
	setup_bonus.c\
	check_map_bonus.c\
	setup_utils_bonus.c\
	files_bonus.c\

# exec
SRC_B +=\
	exec_bonus.c\
	exec_utils_bonus.c\
	exec_tools_bonus.c\
	events_bonus.c\
	events_utils_bonus.c\
	raycasting_bonus.c\
	raycasting_checks_bonus.c\

#          ----------========== {     OBJS     } ==========----------

SRC_DIR = src/
OBJ_DIR = src/obj_dir/
SRCB_DIR = bonus/
OBJB_DIR = bonus/obj_dir/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OBJB = $(addprefix $(OBJB_DIR), $(SRC_B:.c=.o))

VPATH= $(shell find ./ -type d)

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

bonus: $(OBJB_DIR) $(OBJB)
	@make -C lib/libft
	@make -sC lib/minilibx
	@$(CC) $(FLAGS) $(MLX_FLAGS) $(OBJB) $(LIB) $(MLX) -o $(NAME)

$(OBJB_DIR)%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE_B) -c $< -o $@
	@printf "\e[1;42m \e[0;m"

$(OBJB_DIR):
	@mkdir -p $(OBJB_DIR)

clean:
	@make -C lib/libft clean
	@rm -f $(OBJ)
	@rm -f $(OBJB)
	@rm -rf src/obj_dir
	@rm -rf bonus/obj_dir
	@printf "\e[0;31m[.o files deleted]\n\e[0;m"

fclean: clean
	@make -C lib/libft fclean
	@make -C lib/minilibx clean
	@rm -f $(NAME)
	@printf "\e[0;31m[cub3d deleted]\n\e[0;m"

re: fclean all

.PHONY: all clean fclean re bonus