# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 11:48:29 by vipalaci          #+#    #+#              #
#    Updated: 2023/11/29 14:16:08 by vipalaci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOURS #
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# VARIABLES #
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./include
NAME = minishell
INCLUDE = include/

# READLINE
RLINE_INC	= -I/sgoinfre/students/$(USER)/homebrew/opt/readline/include
RLINE_L		= -lreadline -L /sgoinfre/students/$(USER)/homebrew/opt/readline/lib

# OBJECTS #
SRC = main.c lexer.c lexer_utils.c list_utils.c utils.c error.c

SRC_PATH = src/
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

# RULES #
all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(RLINE_INC) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(RLINE_L) -o $(NAME)
	@echo "$(GREEN)#### minishell has been created ####$(COLOR_OFF)"

clean:
	@$(RM) $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME) 
	@echo "$(GREEN)#### minishell cleaned successfuly ####$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re