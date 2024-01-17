# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 11:48:29 by vipalaci          #+#    #+#              #
#    Updated: 2024/01/17 10:48:20 by vipalaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOURS #
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# CASA #
READLINE_DIR = $(shell brew --prefix readline)
FLAG	=	-lreadline -lhistory -L $(READLINE_DIR)/lib
# 42 #
#READLINE_DIR = /sgoinfre/students/$(USER)/homebrew/opt/readline
#FLAG	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

# VARIABLES #
RM = rm -rf
CC = gcc
CFLAGS	=	-Wall -Wextra -Werror -I ./include -I $(READLINE_DIR)/include
NAME = minishell
# INCLUDE = include/

# OBJECTS #
SRC = main.c lexer.c lexer_utils.c lexer_utils_2.c list_utils.c \
		list_utils_2.c utils.c utils_2.c error.c parser.c

SRC_PATH = src/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# RULES #
all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FLAG) -o $(NAME)
	@echo "$(GREEN)#### minishell has been created ####$(COLOR_OFF)"

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME) 
	@echo "$(GREEN)#### minishell cleaned successfuly ####$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re
