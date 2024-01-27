# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vinni <vinni@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/10 20:13:05 by vinni             #+#    #+#              #
#    Updated: 2023/04/11 17:03:03 by vinni            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLOURS #
GREEN = \033[0;32m
COLOR_OFF = \033[0m

# VARIABLES #
LIB = ar rcs
RM = rm -rf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
INCLUDE = include/

# OBJECTS #
MY_SOURCES = ft_is/ft_isdigit.c ft_is/ft_isalpha.c ft_is/ft_isalnum.c ft_is/ft_isascii.c \
	ft_is/ft_isprint.c ft_others/ft_toupper.c ft_others/ft_tolower.c ft_str/ft_strlen.c \
	ft_others/ft_atoi.c ft_mem/ft_memcpy.c ft_mem/ft_memmove.c ft_mem/ft_memset.c \
	ft_mem/ft_memcmp.c ft_str/ft_strchr.c ft_others/ft_bzero.c ft_str/ft_strlcpy.c \
	ft_others/ft_calloc.c ft_str/ft_strjoin.c ft_mem/ft_memchr.c ft_str/ft_strnstr.c \
	ft_str/ft_strlcat.c ft_str/ft_strdup.c ft_str/ft_strrchr.c ft_str/ft_strncmp.c \
	ft_str/ft_substr.c ft_str/ft_strtrim.c ft_str/ft_str_is_int.c ft_str/ft_strmapi.c ft_str/ft_striteri.c \
	ft_put/ft_putchar_fd.c ft_put/ft_putstr_fd.c ft_put/ft_putendl_fd.c ft_put/ft_putnbr_fd.c \
	ft_others/ft_itoa.c ft_others/ft_split.c ft_lst/ft_lstnew.c ft_lst/ft_lstadd_front.c \
	ft_lst/ft_lstsize.c ft_lst/ft_lstlast.c ft_lst/ft_lstadd_back.c ft_lst/ft_lstdelone.c \
	ft_lst/ft_lstclear.c ft_lst/ft_lstiter.c ft_lst/ft_lstmap.c ft_printf/ft_printf.c \
	ft_printf/ft_printhex.c ft_printf/ft_printnbr.c ft_printf/ft_printptr.c ft_printf/ft_printstr.c \
	ft_printf/ft_printuint.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC_DIR = .

MY_OBJECTS = $(addprefix $(OBJ_DIR)/,$(MY_SOURCES:%.c=%.o))
OBJ_DIR = obj

# RULES #
all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@$(LIB)	$(NAME)	$(MY_OBJECTS)
	@echo "$(GREEN)#### Libft has been created ####$(COLOR_OFF)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE) | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)#### Libft cleaned successfully ####$(COLOR_OFF)"

re: fclean all

.PHONY: all clean fclean re
