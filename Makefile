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

all: $(NAME)

$(NAME): serveur client
		@echo CREATE $(NAME)


serveur:
		@(cd $(S_DIR) && $(MAKE))
		mv $(S_DIR)/serveur ./serveur

client:
		@(cd $(C_DIR) && $(MAKE))
		mv $(C_DIR)/client ./client

clean:
		@(cd $(S_DIR) && $(MAKE) $@)
		@(cd $(C_DIR) && $(MAKE) $@)


fclean: clean
		@/bin/rm serveur client

re: fclean all
