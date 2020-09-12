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

NAME = minishell

OBJ_DIR = bin
SRC_DIR = src
HDR_DIR = includes
LIB_DIR = libs

CC = gcc
INCLUDES =  -I./$(LIB_DIR)/libft -I./$(HDR_DIR)
FLAGS = -Wall -Wextra -Werror $(INCLUDES) -O2 -MMD

FILES = $(wildcard $(SRC_DIR)/*.c) \
		$(wildcard $(SRC_DIR)/read_line/*.c) \
		$(wildcard $(SRC_DIR)/clear_command_line/*.c) \
		$(wildcard $(SRC_DIR)/parse_commands/*.c) \
		$(wildcard $(SRC_DIR)/exec_all_commands/*.c) \
		$(wildcard $(SRC_DIR)/builin_functions/*.c)

FILES_O = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

.PHONY: all
all: $(OBJ_DIR) lft $(NAME)
	@echo "\n\033[32m[+] The $(NAME) assembled!\033[0m\n"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/read_line/ \
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/clear_command_line/ \
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/parse_commands/ \
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/exec_all_commands/ \
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)/builin_functions/

.PHONY: lft
lft:
	@$(MAKE) -C ./$(LIB_DIR)/libft --no-print-directory --silent
	@echo "\033[32m[+] Libft is assembled!\033[0m"

$(NAME): $(FILES_O)
	$(CC) $(FLAGS) $(FILES_O) -L./$(LIB_DIR)/libft/ -lft -o $(NAME)

$(FILES_O): $(OBJ_DIR)/%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
include $(wildcard $(OBJ_DIR)/*.d $(OBJ_DIR)/*/*.d $(OBJ_DIR)/*/*/*.d)

.PHONY: clean
clean:
	$(RM) -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	$(RM) -f $(NAME)

.PHONY: re
re: fclean libfclean all

.PHONY: bonus
bonus: all

.PHONY: libfclean
libfclean:
	@$(MAKE) -C ./$(LIB_DIR)/libft --no-print-directory fclean
