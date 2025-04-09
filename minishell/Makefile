# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:55:38 by goteixei          #+#    #+#              #
#    Updated: 2025/04/09 02:07:23 by goteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Colors (for terminal output) ---
RESET			= $(shell printf "\33[0m")
RED				= $(shell printf "\33[31m")
GREEN			= $(shell printf "\33[32m")
WHITE			= $(shell printf "\33[37m")
YELLOW			= $(shell printf "\33[33m")
BLUE			= $(shell printf "\33[34m")

# --- Symbols / Emojis (requires UTF-8 terminal) ---
CHECKMARK		= ✅
CROSSMARK		= ❌
GEAR			= ⚙️
FOLDER			= 📁
SPARKLES		= ✨

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
#MANDATORY_DIR	= $(SRC_DIR)mandatory/
# Using just SRC_DIR

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

#MANDATORY_SRC	= $(MANDATORY_DIR)main.c
MANDATORY_SRC	= $(SRC_DIR)/signals/ms_signal_handlers.c\
				  $(SRC_DIR)/parser/ms_parser_placeholder.c\
				  $(SRC_DIR)/builtin/ms_execute_cd.c\
				  $(SRC_DIR)/builtin/ms_execute_echo.c\
				  $(SRC_DIR)/builtin/ms_execute_env.c\
				  $(SRC_DIR)/builtin/ms_execute_exit.c\
				  $(SRC_DIR)/builtin/ms_execute_export.c\
				  $(SRC_DIR)/builtin/ms_execute_pwd.c\
				  $(SRC_DIR)/builtin/ms_execute_unset.c\
				  $(SRC_DIR)/exec/ms_exec_external.c\
				  $(SRC_DIR)/exec/ms_path_handler.c\
				  $(SRC_DIR)main.c

# Object files in the same directory as source
MANDATORY_OBJ	= $(MANDATORY_SRC:.c=.o)

# -------------------------------------------------------------
# MANDATORY
# RULES
# -------------------------------------------------------------

all:			$(NAME)

$(NAME):		$(LIBFT_A) $(MANDATORY_OBJ) 
				@echo "$(YELLOW)Compiling $(NAME) (Mandatory)...$(RESET)"
				@$(CC) $(CFLAGS) $(MANDATORY_OBJ) $(LIBFT_A) -o $(NAME) -lreadline
				@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"
				@echo "$(GREEN)+---------------------------------------------+"
				@echo "|                                             |"
				@echo "|       $(CHECKMARK) $(NAME) build successful!        |"
				@echo "|                                             |"
				@echo "+---------------------------------------------+$(RESET)"

$(LIBFT_A):
				@echo "$(RED)Libft library ($(LIBFT_A)) not found or needs update. Preparing Libft...$(RESET)"
				@echo "Removing old Libft repository clone (if any)..."
				@$(RM) $(LIBFT_REPO_DIR)
				@echo "Creating parent directory $(LIB_DIR)..."
				@mkdir -p $(LIB_DIR)
				@echo "Cloning $(LIBFT_REPO_URL) into $(LIBFT_REPO_DIR)...$(RESET)"
				@git clone --depth 1 $(LIBFT_REPO_URL) $(LIBFT_REPO_DIR) || (echo "$(RED)ERROR: Clone failed$(RESET)" && exit 1)
				@echo "$(YELLOW)Compiling Libft in $(LIBFT_SRC_DIR)...$(RESET)"
				@make -s -C $(LIBFT_SRC_DIR) > /dev/null || (echo "ERROR: Libft make failed" && exit 1)
				@echo "$(GREEN)Libft compiled successfully!$(RESET)"

# --- Cleaning Rules ---

clean:
				@echo "$(YELLOW)Object files cleaning start$(RESET)"
				@echo "Cleaning project objects..."
				@$(RM) $(MANDATORY_OBJ)
				@echo "Cleaning Libft objects (if possible)..."
				@-if [ -d "$(LIBFT_SRC_DIR)" ]; then make -s -C $(LIBFT_SRC_DIR) clean; fi
				@echo "$(GREEN)Object files cleaned successfully!$(RESET)"

fclean:			clean
				@echo "$(YELLOW)Executable files cleaning start$(RESET)"
				@echo "Cleaning executable $(NAME)..."
				@$(RM) $(NAME)
				@echo "Cleaning Libft library (if possible)..."
				@-if [ -d "$(LIBFT_SRC_DIR)" ]; then make -s -C $(LIBFT_SRC_DIR) fclean; fi
				@echo "Removing entire Libft repository clone directory $(LIBFT_REPO_DIR)..."
				@$(RM) $(LIBFT_REPO_DIR)
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
