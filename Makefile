# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 03:00:00 by oligrien          #+#    #+#              #
#    Updated: 2025/08/17 02:47:36 by ndehmej          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = Cube_3D

CC			= cc
FLAGS		= -Wall -Wextra -Werror

SRCS_DIR    = src/
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
			$(PRS_DIR)parser_utils.c

SRCS        = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS        = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -g -c $< -o $@

$(NAME): $(OBJS) $(MLXLIB) | $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLXLIB) -ldl -lglfw -pthread -lm -g -o $(NAME)
	@echo "Program compiled\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

all: $(LIBFT) $(NAME)

$(MLXLIB):
	@cmake $(MLXFOLDER) -B $(MLXFOLDER)/build
	@make -C $(MLXFOLDER)/build -j4
	@echo "MLX Compiled"

clean:
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@rm -rf $(MLXFOLDER)/build
	@echo "Removing objects & MLX42"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@echo "Cleaning all"

re: fclean all

.PHONY: all clean fclean re
