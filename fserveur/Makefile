#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: espiroux <espiroux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/11 12:43:05 by espiroux          #+#    #+#              #
#    Updated: 2013/12/17 12:29:57 by espiroux         ###   ########.fr        #
#                                                                              #
#******************************************************************************#


export CC= gcc
export CFLAGS= -Werror -Wall -Wextra

MLX_FLAGS= -lmlx -lXext -lX11
NAME=serveur
LIBFT_DIR=libft/
LIBMLX_DIR=/usr/X11/lib
INC_DIR=includes/
SRC_DIR=src/

FT_C=$(SRC_DIR)ft_p.c $(SRC_DIR)send_confirmation.c $(SRC_DIR)options/option_ls.c\
$(SRC_DIR)options/option_pwd.c $(SRC_DIR)ft_getINode.c \
$(SRC_DIR)options/option_cd.c \
$(SRC_DIR)autorized_folder.c \
$(SRC_DIR)options/option_get.c \
$(SRC_DIR)options/option_set.c \
$(SRC_DIR)error/error_open.c \
$(SRC_DIR)error/error_open_dir.c \
$(SRC_DIR)is_autorized.c \
$(SRC_DIR)redirect_stdout.c \
$(SRC_DIR)close_redirect_stdout.c \
$(SRC_DIR)wait_response.c \
$(SRC_DIR)do_command_line.c

FT_O=$(FT_C:.c=.o)

all: $(NAME)

$(NAME): a
		@echo CREATE $(NAME)
		@gcc $(CFLAGS) -I $(INC_DIR) $(FT_C) ./libft/libft.a -o $(NAME) -g

a:
		@(cd $(LIBFT_DIR) && $(MAKE))

clean:
		@(cd $(LIBFT_DIR) && $(MAKE) $@)
		@/bin/rm -rf $(NAME).dSYM


fclean: clean
		@/bin/rm $(NAME)

re: fclean all
