# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:55:38 by goteixei          #+#    #+#              #
#    Updated: 2025/04/06 15:17:02 by goteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors (for terminal output) ---
RESET			= $(shell printf "\33[0m")
RED				= $(shell printf "\33[31m")
GREEN			= $(shell printf "\33[32m")
WHITE			= $(shell printf "\33[37m")
YELLOW			= $(shell printf "\33[33m")
BLUE			= $(shell printf "\33[34m")

# --- Program Name ---
NAME 			= minishell

# Directories
INC_DIR			= inc/
LIB_DIR			= lib/
SRC_DIR			= src/

LIBFT_DIR		= lib/libft/
MANDATORY_DIR	= $(SRC_DIR)mandatory/

# Libraries
LIBFT			= $(LIBFT_DIR)libft.a

# --- Compiler and Flags ---
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS			+= -I$(LIBFT_DIR) -I$(INC_DIR)

# -------------------------------------------------------------
# MANDATORY
# -------------------------------------------------------------

MANDATORY_SRC	= $(MANDATORY_DIR)main.c\

# Object files in the same directory as source
MANDATORY_OBJ	= $(MANDATORY_SRC:.c=.o)

# -------------------------------------------------------------
# MANDATORY
# RULES
# -------------------------------------------------------------

all:			$(NAME)

$(NAME):		$(MANDATORY_OBJ) $(LIBFT)
				@echo "$(YELLOW)Compiling $(NAME) (Mandatory)...$(RESET)"
				@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT) -o $(NAME)
				@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
				@echo "$(YELLOW)Compiling $(LIBFT)...$(RESET)"
				@$(MAKE) -s -C $(LIBFT_DIR)
				@echo "$(GREEN)$(LIBFT) compiled successfully!$(RESET)"

clean:
				@echo "$(YELLOW)Cleaning object files...$(RESET)"
				$(RM) $(MANDATORY_OBJ)
				@$(MAKE) -s -C $(LIBFT_DIR) clean
				@echo "$(GREEN)Object files cleaned successfully!$(RESET)"

fclean:			clean
				@echo "$(YELLOW)Cleaning executable files...$(RESET)"
				$(RM) $(NAME)
				@$(MAKE) -s -C $(LIBFT_DIR) fclean
				@echo "$(GREEN)Executable files cleaned successfully!$(RESET)"

re:				fclean all

valgrind:		all
				@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
					--track-origins=yes --trace-children=yes --suppressions=readline.supp ./minishell

.PHONY:			all clean fclean re bonus

#.SILENT

# add rule test for valgrind
