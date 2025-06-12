# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 22:48:46 by goteixei          #+#    #+#              #
#    Updated: 2025/04/18 16:26:51 by goteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Program Name ---
NAME = libft.a

# --- Directories ---
SRC_DIR = .
FT_PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

# --- Compiler and Flags ---
CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g
CFLAGS			+= -I.

# --- Directories ---
SRC_DIR = .
FT_PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

SRCS	= ft_isalpha.c\
		ft_isdigit.c\
		ft_isascii.c\
		ft_isalnum.c\
		ft_isprint.c\
		ft_strlen.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strncmp.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strnstr.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_strdup.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_striteri.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\
		ft_putendl.c\
		ft_putstr.c\
		ft_putchar.c\
		ft_atol.c\
		ft_error.c\
		ft_atoi_base.c\
		ft_abs.c\
		ft_max.c\
		ft_min.c\
		ft_strcmp.c

# Source files for ft_printf
FT_PRINTF_SRCS = $(FT_PRINTF_DIR)/ft_printf.c \
				 $(FT_PRINTF_DIR)/ft_print_char.c \
				 $(FT_PRINTF_DIR)/ft_print_str.c \
				 $(FT_PRINTF_DIR)/ft_print_ptr.c \
				 $(FT_PRINTF_DIR)/ft_print_unsigned.c \
				 $(FT_PRINTF_DIR)/ft_print_hex.c \
				 $(FT_PRINTF_DIR)/ft_print_int.c \
				 $(FT_PRINTF_DIR)/ft_print_percent.c

# Source files for get_next_line
GNL_SRCS		= $(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c

# --- Object Files ---
OBJS = $(SRCS:.c=.o)
FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

ALL_OBJS = $(OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)

# --- Rules ---
all:			$(NAME)

$(NAME):		$(ALL_OBJS)
				ar rcs $(NAME) $(ALL_OBJS)

%.o: %.c
				@echo "libft: Compiling $<..."
				$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF_DIR)/%.o: $(FT_PRINTF_DIR)/%.c
				@echo "ft_printf: Compiling $<..."
				$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
				@echo "get_next_line: Compiling $<..."
				$(CC) $(CFLAGS) -c $< -o $@
	
clean:
				@echo "Cleaning object files..."
				$(RM) $(ALL_OBJS)

fclean:			clean
				@echo "Cleaning library archive..."
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re

# .SILENT
