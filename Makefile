# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/10 17:29:48 by zkerriga          #+#    #+#              #
#    Updated: 2020/09/10 17:33:10 by zkerriga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
OBJ_DIR=bin

.PHONY: all
all:
	echo "kek"

.PHONY: clean
clean:
	$(RM) -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) -f $(NAME)

.PHONY: re
re: fclean all
