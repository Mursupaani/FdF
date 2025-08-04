# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 13:06:22 by anpollan          #+#    #+#              #
#    Updated: 2025/07/25 12:13:21 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
LIBFT		= ./libft/libft.a
MLX			= ./mlx/libmlx_Linux.a
SRCS_DIR	= ./srcs/
INCL_DIR	= ./incl/
SRCS 		= ./srcs/main.c \
			  ./srcs/memory_and_error.c \
			  ./srcs/parsing.c \
			  ./srcs/parsing_utils.c \
			  ./srcs/draw_pixels.c \
			  ./srcs/calculate_projection.c \
			  ./srcs/line_drawing.c \
			  ./srcs/line_drawing2.c \
			  ./srcs/hooks.c \
			  ./srcs/manipulate_view.c \
			  ./srcs/resetting.c \
			  ./srcs/fdf_utils.c
OBJS 		= $(SRCS:%.c=%.o)
HEADER		= ./incl/fdf.h
C_FLAGS		= -Wall -Wextra -Werror -g
MLXFLAGS	= -lXext -lX11 -lm

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
