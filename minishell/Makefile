# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 15:55:38 by goteixei          #+#    #+#              #
#    Updated: 2025/07/01 11:17:27 by jpedro-f         ###   ########.fr        #
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
#LIBFT_REPO_DIR	= $(LIB_DIR)libft_repo/
# Path to the actual Libft source code *inside* the cloned repository
LIBFT_SRC_DIR	= $(LIB_DIR)libft/
# Path to the compiled libft.a file (TARGET FILE)
LIBFT_A			= $(LIBFT_SRC_DIR)libft.a
# Libft Repository URL
#LIBFT_REPO_URL	= https://github.com/jvieira96/42_libft.git

# --- Source Directories ---
#MANDATORY_DIR	= $(SRC_DIR)mandatory/
# Using just SRC_DIR

# Libraries
LIBFT			= $(LIBFT_DIR)libft.a

# --- Compiler and Flags ---
CC				= cc
RM				= rm -rf
SAN_FLAGS		= -fsanitize=address
SAN_FLAGS		+= -fsanitize=leak
SAN_FLAGS		+= -fsanitize=undefined
SAN_FLAGS		+= -fno-omit-frame-pointer
CFLAGS			=  -Wall -Wextra -Werror -g
#CFLAGS			+= $(SAN_FLAGS)
CFLAGS			+= -I$(INC_DIR)
CFLAGS			+= -I$(LIBFT_SRC_DIR)
#CFLAGS			+= -I$(LIBFT_SRC_DIR)
LDFLAGS			= $(SAN_FLAGS)

# -------------------------------------------------------------
# MANDATORY
# -------------------------------------------------------------

#MANDATORY_SRC	= $(MANDATORY_DIR)main.c
MANDATORY_SRC	= $(SRC_DIR)/signals/ms_signal_handlers.c\
				  $(SRC_DIR)/signals/ms_signal_handler_non_int.c\
				  $(SRC_DIR)/signals/ms_debug_global_signal.c\
				  $(SRC_DIR)/signals/ms_signals_heredoc.c\
				  $(SRC_DIR)/signals/ms_signals_exit.c\
				  $(SRC_DIR)/syntax_check/ms_syntax_utils.c\
				  $(SRC_DIR)/syntax_check/ms_syntax_check.c\
				  $(SRC_DIR)/syntax_check/ms_debug_input.c\
				  $(SRC_DIR)/parsing/ms_parsing.c\
				  $(SRC_DIR)/parsing/ms_main_parsing.c\
				  $(SRC_DIR)/parsing/ms_parsing_utils.c\
				  $(SRC_DIR)/execution/ms_tree_exec.c\
				  $(SRC_DIR)/execution/ms_tree_exec_utils.c\
				  $(SRC_DIR)/execution/ms_exec_cmd.c\
				  $(SRC_DIR)/execution/ms_exec_cmd_utils.c\
				  $(SRC_DIR)/execution/ms_exec_heredoc.c\
				  $(SRC_DIR)/execution/ms_exec_pipe.c\
				  $(SRC_DIR)/execution/ms_exec_redir.c\
				  $(SRC_DIR)/cleanup/ms_cleanup.c\
				  $(SRC_DIR)/cleanup/ms_cleanup_2.c\
				  $(SRC_DIR)/tokenization/ms_quotes.c\
				  $(SRC_DIR)/tokenization/ms_quotes_cmd.c\
				  $(SRC_DIR)/tokenization/ms_expansion_check.c\
				  $(SRC_DIR)/tokenization/ms_tokenization.c\
				  $(SRC_DIR)/tokenization/ms_tokenization_utils.c\
				  $(SRC_DIR)/tokenization/ms_tokenization_utils2.c\
				  $(SRC_DIR)/tokenization/ms_tokenization_utils3.c\
				  $(SRC_DIR)/tokenization/ms_list_utils.c\
				  $(SRC_DIR)/expand/ms_expand_var.c\
				  $(SRC_DIR)/expand/ms_expand_var_2.c\
				  $(SRC_DIR)/expand/ms_expand_var_3.c\
				  $(SRC_DIR)/expand/ms_expand_var_utils.c\
				  $(SRC_DIR)/builtin/ms_execute_cd.c\
				  $(SRC_DIR)/builtin/ms_execute_echo.c\
				  $(SRC_DIR)/builtin/ms_execute_env.c\
				  $(SRC_DIR)/builtin/ms_execute_exit.c\
				  $(SRC_DIR)/builtin/ms_execute_exit_utils.c\
				  $(SRC_DIR)/builtin/ms_execute_export.c\
				  $(SRC_DIR)/builtin/ms_execute_export_print.c\
				  $(SRC_DIR)/builtin/ms_execute_export_utils.c\
				  $(SRC_DIR)/builtin/ms_execute_export_utils_2.c\
				  $(SRC_DIR)/builtin/ms_execute_pwd.c\
				  $(SRC_DIR)/builtin/ms_execute_unset.c\
				  $(SRC_DIR)/builtin/ms_execute_unset_utils.c\
				  $(SRC_DIR)/builtin/ms_utils_getenv.c\
				  $(SRC_DIR)/builtin/ms_utils_setenv.c\
				  $(SRC_DIR)/init/ms_init_struct.c\
				  $(SRC_DIR)/utils/ms_utils_exit.c\
				  $(SRC_DIR)/utils/ms_utils_pid.c\
				  $(SRC_DIR)/prompt/ms_prompt.c\
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
#				@echo "$(RED)Libft library ($(LIBFT_A)) not found or needs update. Preparing Libft...$(RESET)"
#				@echo "Removing old Libft repository clone (if any)..."
#				@$(RM) $(LIBFT_REPO_DIR)
#				@echo "Creating parent directory $(LIB_DIR)..."
#				@mkdir -p $(LIB_DIR)
#				@echo "Cloning $(LIBFT_REPO_URL) into $(LIBFT_REPO_DIR)...$(RESET)"
#				@git clone --depth 1 $(LIBFT_REPO_URL) $(LIBFT_REPO_DIR) || (echo "$(RED)ERROR: Clone failed$(RESET)" && exit 1)
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
#				@echo "Cleaning Libft library (if possible)..."
#				@-if [ -d "$(LIBFT_SRC_DIR)" ]; then make -s -C $(LIBFT_SRC_DIR) fclean; fi
#				@echo "Removing entire Libft repository clone directory $(LIBFT_REPO_DIR)..."
#				@$(RM) $(LIBFT_REPO_DIR)
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
# valgrind:		all
# 				@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
# 					--track-origins=yes --trace-children=yes ./minishell

# reval: re valgrind

# valgrind_sup:		all
# 				@valgrind -q --leak-check=full --show-leak-kinds=all \
# 				--suppressions=readline.supp --track-fds=yes ./minishell

# reval_sup: re valgrind_sup

.PHONY:			all clean fclean re valgrind reval valgrind_sup reval_sup

#.SILENT
