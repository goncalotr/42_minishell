# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 12:01:49 by goteixei          #+#    #+#              #
#    Updated: 2025/04/07 11:37:22 by goteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_printf.c\
		ft_print_char.c\
		ft_print_str.c\
		ft_print_ptr.c\
		ft_print_unsigned.c\
		ft_print_hex.c\
		ft_print_int.c\
		ft_print_percent.c

OBJS	= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f 
CFLAGS			= -Wall -Wextra -Werror
NAME			= libftprintf.a

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

clean:			
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re

# .SILENT:
