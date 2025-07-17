# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/07/15 19:00:09 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#WARN: Remove print matrix

NAME		= fdf
LIBFT		= ./libft/libft.a
MLX			= ./mlx/libmlx_Linux.a
SRCS_DIR	= ./srcs/
INCL_DIR	= ./incl/
SRCS 		= ./srcs/main.c \
			  ./srcs/memory_and_error.c \
			  ./srcs/fdf.c \
			  ./srcs/parsing.c \
			  ./srcs/print_matrix.c
OBJS 		= $(SRCS:%.c=%.o)
HEADER		= ./incl/fdf.h
C_FLAGS		= -Wall -Wextra -Werror -g
MLXFLAGS	= -lXext -lX11 -lm
#MLXFLAGS	= -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(C_FLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c $(HEADER)
	cc $(C_FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME) compile_commands.json
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
