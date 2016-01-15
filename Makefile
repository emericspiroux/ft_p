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

NAME = ft_p
S_DIR = ./fserveur
C_DIR = ./fclient
LIBFT_DIR=libft/

.PHONY: clean, fclean, re

all: $(NAME)

$(NAME):lib serveurnolib clientnolib

lib:
		@(cd $(LIBFT_DIR) && $(MAKE))

serveurnolib:
		@(cd $(S_DIR) && $(MAKE) nolibft)
		@(mv $(S_DIR)/serveur ./serveur)

clientnolib:
		@(cd $(C_DIR) && $(MAKE) nolibft)
		@(mv $(C_DIR)/client ./client)

serveur:
		@(cd $(S_DIR) && $(MAKE))
		mv $(S_DIR)/serveur ./serveur

client:
		@(cd $(C_DIR) && $(MAKE))
		mv $(C_DIR)/client ./client

clean:
		@(cd $(S_DIR) && $(MAKE) $@)
		@(cd $(C_DIR) && $(MAKE) $@)
		@(cd $(LIBFT_DIR) && $(MAKE) $@)


fclean: clean
		@(cd $(LIBFT_DIR) && $(MAKE) $@)
		@/bin/rm serveur client

re: fclean all
