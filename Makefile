# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/08/22 00:17:31 by ndehmej          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = Cube_3D

CC			= cc
FLAGS		= -Wall -Wextra -Werror -g

SRCS_DIR    = src/
UTL_DIR		= utils/
# TXT_DIR		= textures/
PRS_DIR     = parser/
OBJS_DIR    = obj/
LIBFT_DIR   = libft/
GC_DIR      = gc/
MLXFOLDER   = MLX42

INCLUDES    = -Iincludes -I$(LIBFT_DIR)/includes -I$(GC_DIR)/includes -I$(MLXFOLDER)/include

LIBFT       = $(LIBFT_DIR)/libft.a
GC          = $(GC_DIR)/gc.a
MLXLIB      = $(MLXFOLDER)/build/libmlx42.a

SRCS_FILES  = main.c \
			$(UTL_DIR)utils.c \
			$(PRS_DIR)parser_utils.c \
			$(PRS_DIR)check_map.c \
			$(PRS_DIR)check_path.c \
			$(PRS_DIR)store.c \
			$(PRS_DIR)mlx.c \
			$(PRS_DIR)move.c \
			
SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

# Compilation des .o
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@


# Règle de build principale
$(NAME): $(OBJS) $(LIBFT) $(GC) $(MLXLIB)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(GC) $(MLXLIB) -ldl -lglfw -pthread -lm -o $(NAME)
	@echo "Program compiled"

# Compilation de libft
$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "libft built."

# Compilation du garbage collector
$(GC): $(LIBFT)
	@echo "Building gc..."
	@$(MAKE) -C $(GC_DIR) LIBFT_PATH="../libft"
	@echo "gc built."

# Compilation de MLX
$(MLXLIB):
	@cmake $(MLXFOLDER) -B $(MLXFOLDER)/build
	@make -C $(MLXFOLDER)/build -j4
	@echo "MLX Compiled"

# Règles standards
all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(GC_DIR) clean > /dev/null
	@rm -rf $(MLXFOLDER)/build
	@echo "Cleaning objects, MLX, libft and gc"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@$(MAKE) -C $(GC_DIR) fclean > /dev/null
	@echo "Full clean"

re: fclean all

.PHONY: all clean fclean re
