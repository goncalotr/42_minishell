# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:55:38 by goteixei          #+#    #+#              #
#    Updated: 2025/04/07 13:56:59 by goteixei         ###   ########.fr        #
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

# --- Libft Setup ---
# Directory where the Libft repository will be cloned
LIBFT_REPO_DIR	= $(LIB_DIR)libft_repo/
# Path to the actual Libft source code *inside* the cloned repository
LIBFT_SRC_DIR	= $(LIBFT_REPO_DIR)libft/
# Path to the compiled libft.a file (TARGET FILE)
LIBFT_A			= $(LIBFT_SRC_DIR)libft.a
# Libft Repository URL
LIBFT_REPO_URL	= https://github.com/goncalotr/42_libft_v2.git

# --- Source Directories ---
MANDATORY_DIR	= $(SRC_DIR)mandatory/

# Libraries
LIBFT			= $(LIBFT_DIR)libft.a

# --- Compiler and Flags ---
CC				= cc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS			+= -I$(INC_DIR)
CFLAGS			+= -I$(LIBFT_SRC_DIR)

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

$(NAME):		$(MANDATORY_OBJ) $(LIBFT_LIB)
				@echo "$(YELLOW)Compiling $(NAME) (Mandatory)...$(RESET)"
				@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT_LIB) -o $(NAME) -lreadline
				@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT_LIB):
				@echo "Libft library not found. Preparing Libft..."
				@echo "-- Removing old Libft repository clone (if any)..."
				@$(RM) $(LIBFT_REPO_DIR)
				@echo "-- Creating parent directory $(LIB_DIR)..."
				@mkdir -p $(LIB_DIR)
				@echo "-- Cloning $(LIBFT_REPO_URL) into $(LIBFT_REPO_DIR)..."
				@$git clone --depth 1 $(LIBFT_REPO_URL) $(LIBFT_REPO_DIR) || (echo "ERROR: Clone failed" && exit 1)
				@echo "-- Compiling Libft in $(LIBFT_SRC_DIR)..."
				@$(MAKE) -C $(LIBFT_SRC_DIR) || (echo "ERROR: Libft make failed" && exit 1)
				@echo "Libft compiled."

# --- Cleaning Rules ---

clean:
				@echo "Cleaning project objects..."
				@$(RM) $(MANDATORY_OBJ)
				@echo "Cleaning Libft objects (if possible)..."
				@-$(MAKE) -s -C $(LIBFT_SRC_DIR) clean
				@echo "$(GREEN)Object files cleaned successfully!$(RESET)"

fclean:			clean
				@echo "Cleaning executable $(NAME)..."
				@$(RM) $(NAME)
				@echo "Cleaning Libft library (if possible)..."
				@-$(MAKE) -s -C $(LIBFT_SRC_DIR) fclean
				@echo "Removing entire Libft repository clone directory $(LIBFT_CLONE_DIR)..."
				@$(RM) $(LIBFT_CLONE_DIR)
				@echo "$(GREEN)Clean complete.$(RESET)"

re:				fclean all

# --- Utility Rules ---

# Rule to force re-downloading libft
#update_libft:
#				@echo "$(YELLOW)Removing existing libft to force re-download...$(RESET)"
#				@rm -rf $(LIBFT_DIR)
#				@$(MAKE) $(LIBFT_CHECK_FILE)
#				@echo "$(GREEN)Use 'make' or 'make all' to recompile everything.$(RESET)"

# Rule to use valgrind
valgrind:		all
				@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
					--track-origins=yes --trace-children=yes --suppressions=readline.supp ./minishell

.PHONY:			all clean fclean re valgrind

#.SILENT
