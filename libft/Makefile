# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 13:18:29 by anpollan          #+#    #+#              #
#    Updated: 2025/04/28 19:09:29 by anpollan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
SRCS		= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			  ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			  ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			  ft_printf.c ft_print_char.c ft_print_decimal.c \
			  ft_print_integer.c ft_print_lowercase_hex.c ft_print_num_in_hex.c \
			  ft_print_percentage.c ft_print_pointer.c ft_print_string.c \
			  ft_print_unsigned_decimal.c ft_print_uppercase_hex.c \
			  get_next_line_bonus.c get_next_line_utils_bonus.c \
			  ft_atoi_hexadecimal.c ft_atoi_safe.c
OBJS		= $(SRCS:%.c=%.o)
BONUS		= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			  ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			  ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
BONUS_OBJS	= $(BONUS:%.c=%.o)
CC			= cc
C_FLAGS		= -Wall -Wextra -Werror -c -g -I.
AR			= ar
AR_FLAGS	= -rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(C_FLAGS) $< -o $@

bonus: .bonus

.bonus: $(NAME) $(BONUS_OBJS)
	$(AR) $(AR_FLAGS) $(NAME) $(BONUS_OBJS)
	touch .bonus

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)
	
fclean:	clean
	rm -rf $(NAME) .bonus compile_commands.json

re: fclean all

.PHONY: all bonus clean fclean re
