# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 16:08:21 by whendrik          #+#    #+#              #
#    Updated: 2024/03/05 20:04:14 by whendrik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FLAGS
CC = gcc
C_FLAGS = -Wall -Wextra -Werror -g -o3
M_FLAGS = -Llibft -Imlx -Lmlx -Lmlx -framework OpenGL -framework AppKit
# S_FLAGS = -g -fsanitize=address,undefined

#commands
RM = rm -rf
AR = ar rc

#Targlib name and dirs
NAME = Cub3D
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
SRC_DIR = src
SRC_FILES = main.c rc_draw_map.c rc_init_data.c rc_draw_ray.c rc_draw_utils.c rc_cast_ray.c\
		ps_check_args.c ps_check_grid.c ps_check_textures.c ps_check_walls.c \
		ps_error.c ps_init_grid.c ps_init_mapinfo.c ps_main_justin.c \
		ps_texture_utils.c ps_validate_cubfile.c \
		
OBJ_DIR = obj
INC_DIR = includes
MLX_DIR = mlx
LIBFT_DIR = libft
INCS = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Sources, objects and dependencies
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJECTS = $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)

# Default target, build the library
all: $(LIBFT_DIR) $(MLX_DIR) $(NAME)

# Rule to build each personal library
$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

# Object file build rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@


$(NAME): $(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(C_FLAGS) $^ $(M_FLAGS) $(INCS) -o $(NAME)

# Clean object files
clean:
	$(RM) $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

# Clean object files and target library
fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT_DIR)/libft.a
	$(RM) $(MLX_DIR)/libmlx.a
	make fclean -C $(LIBFT_DIR) 

re: fclean all

# Check code style
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c ;
	@norminette -R CheckDefine $(INC_DIR)/*.h ;
	@norminette -R CheckForbiddenSourceHeader $(LIBFT_DIR)/src/*.c ;
	@norminette -R CheckDefine $(LIBFT_DIR)/includes/*.h

# Phony targets
.PHONY: clean all fclean re norm
