# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/23 19:36:01 by heynard           #+#    #+#              #
#    Updated: 2019/02/11 09:59:12 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ssl

INCLU_DIR = includes
BUILD_DIR = objs

SRCS = main.c\
		digest_prog.c\
		commands.c\
		cmd_var.c\
		digest_arguments.c\
		digest_usages.c\
		digest_data.c\
		get_data.c\
		algo_md5.c\
		functions_md5.c\
		functions_bits.c\
		ft_memjoin.c\
		algo_sha256.c\
		functions_sha256.c\
		algo_padding.c\
		buffer_to_string.c

OBJS := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(SRCS)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS= -L./libft -lft

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OBJS)
	@make -C libft
	$(CC) $(CFLAGS) $(LFLAGS) -I $(INCLU_DIR) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: srcs/%.c
	$(CC) -c $< -o $@ -I $(INCLU_DIR)

$(BUILD_DIR):
	@mkdir -p $@

.PHONY: all clean fclean re

clean:
#	@make -C libft clean
	rm -rf $(OBJS) $(BUILD_DIR)

fclean: clean
#	@make -C libft fclean
	rm -f $(NAME)

lib:
	@make -C libft

libclean:
	@make -C libft clean

libfclean:
	@make -C libft fclean

re: fclean all
