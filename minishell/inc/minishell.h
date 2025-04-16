/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:47:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/16 18:05:52 by jpedro-f         ###   ########.fr       */
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
# include <limits.h>
# include <stdbool.h>

// signals
# include <signal.h>

// waitpid
# include <sys/wait.h> 

//stat/access???
# include <sys/stat.h>

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

typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;

typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;
	struct s_redirection	*next;
}	t_redirection;

typedef enum e_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND
}	t_type;

typedef struct s_tokens
{
	char				*token;
	t_type				type;
	struct s_tokens		*next;
}	t_tokens;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// signals
void	ms_signal_handlers_init(void);

// parsing
// ms_list_utils.c
t_tokens *ms_last_node(t_tokens *list);
t_tokens *ms_append_node(t_tokens *list, char  *input, t_type type);
void ms_print_list(t_tokens *list);

// ms_syntax_check.c
bool ms_unclosed_quotes(t_tokens *list);
bool ms_syntax_check(t_tokens *list);
bool ms_pipes_placement(t_tokens *list);

//ms_tokenization.c
t_tokens *ms_extract_operator(char *input, int *i, t_tokens *list);
t_tokens	*ms_extract_word(char *input, int *i, t_tokens *list);
void ms_tokenization(char *input);

// placeholder
void	ms_free_split_args(char **args);
char	**ms_parse_input_placeholder(const char *input_line);
int		ms_execute_command_placeholder(char **args, char **envp);

// built-ins
int		ms_execute_cd(char **args);
int		ms_execute_echo(char **args);
int		ms_execute_env(char **args, char **envp);
int		ms_execute_exit(char **args);
//int		ms_execute_export(char **args);
//int		ms_execute_export(char **args, char ***envp_ptr)
int		ms_execute_pwd(char **args);
//int		ms_execute_unset(char **args);

// exec
int	ms_execute_external_command(char **args, char **envp);

// main
//void	ms_core_loop(char **envp);
//int	main(int argc, char **argv, char **envp);

#endif