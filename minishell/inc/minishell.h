/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:47:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/07 18:24:47 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**************************************************************************
 * SECTION: Libraries
 **************************************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <string.h>
# include <errno.h>

// signals
# include <signal.h>

// readline, add_history
# include <readline/readline.h>
# include <readline/history.h>

// non-standard librarys
# include "../lib/libft_repo/libft/libft.h"

/**************************************************************************
 * SECTION: Macros
 **************************************************************************/

// Colors
# define RESET		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define WHITE		"\033[37m"

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// signals
void	ms_signal_handlers_init(void);

// parsing

// placeholder
void	ms_free_split_args(char **args);
char	**ms_parse_input_placeholder(const char *input_line);
int	ms_execute_command_placeholder(char **args);

// built-ins
int	ms_execute_cd(char **args);
//int	ms_execute_echo(char **args);
//int	ms_execute_env(char **args);
//int	ms_execute_exit(char **args);
//int	ms_execute_export(char **args);
int	ms_execute_pwd(char **args);
//int	ms_execute_unset(char **args);

// main


#endif