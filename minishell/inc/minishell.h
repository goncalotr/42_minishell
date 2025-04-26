/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:47:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/26 17:42:02 by goteixei         ###   ########.fr       */
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

// --- ANSI Color Codes ---
# define RESET   "\033[0m"
# define BLACK   "\033[0;30m"
# define RED     "\033[0;31m"
# define GREEN   "\033[0;32m"
# define YELLOW  "\033[0;33m"
# define BLUE    "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN    "\033[0;36m"
# define WHITE   "\033[0;37m"

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

/*
typedef enum e_redir_type
{
	REDIR_NONE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;
*/

/*
typedef struct s_redirection
{
	t_redir_type			type;
	char					*target;
	struct s_redirection	*next;
}	t_redirection;
*/

typedef enum e_token_type
{
	TOKEN_WORD,				// 0 words
	TOKEN_CMD,				// 1 commands
	TOKEN_PIPE,				// 2 |
	TOKEN_REDIR_IN,			// 3 <
	TOKEN_REDIR_OUT,		// 4 >
	TOEKN_APPEND,			// 5 >>
	TOKEN_HEREDOC,			// 6 <<
	TOKEN_SIMPLE_QUOTE,		// 7 "
	TOKEN_DOUBLE_QUOTE,		// 8 '
}	t_token_type;

typedef struct s_redirection
{
	t_token_type			type;
	char					*target;
	struct s_redirection	*next;
}	t_redirection;


typedef struct s_token
{
	char					*value;
	int						type;
	int						size;
	int						quotes_type;
	struct s_token			*previous;
	struct s_token			*next;
}	t_token;

/**
 * @brief Holds the main state of the minishell.
 *
 * @param environ_list    A dynamically allocated copy of the environment
 * variables
 *(char ** array, NULL-terminated, e.g., {"VAR=value", NULL}).
 *                        This is the list modified by export/unset.
 * @param last_exit_status The exit status of the most recently executed
 * foreground command ($?).
 * @param stdin_fd         Saved original standard input file descriptor
 * (usually 0).
 * @param stdout_fd        Saved original standard output file descriptor
 * (usually 1).
 * @param stderr_fd        Saved original standard error file descriptor
 * (usually 2).
 * @param shell_name       The name the shell was invoked with (argv[0]),
 * useful for errors.
 * @param current_cmd_table Pointer to the currently parsed command structure
 * (optional, can also be passed as function arguments).
 * Manage lifecycle carefully.
 * @param envp_orig        Pointer to the original envp from main
 * (optional, for reference).
 */
typedef struct s_minishell
{
	char	**envp;
	int		last_exit_status;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	char	*shell_name;
	char	**envp_orig;
}	t_minishell;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// --- main ---
//void	ms_core_loop(char **envp);
//int	main(int argc, char **argv, char **envp);

// --- prompt ---
char	*ms_get_prompt(int last_status);

// --- debug ---
void	ms_debug_print_args(char **args);
void	ms_debug_print_gsig(void);

// --- init ---
int		init_shell_data(t_minishell *data, char **argv, char **envp);

// --- signals ---
void	ms_signal_handlers_init(void);

// --- parsing ---

// parsing placeholder 
void	ms_free_split_args(char **args);
char	**ms_parse_input_placeholder(const char *input_line);
int		ms_execute_command_placeholder(char **args, char **envp, t_minishell *data);

// --- expand ---

// utils
int		ms_valid_var(char c, int mode);
int		ms_expand_error(char **args, int i, int mode);
int		ms_find_next_dollar(const char *str, int start_pos);
char	*ms_get_expansion_value(const char *info, int last_exit_status);
int		ms_append_and_free(char **base_str_ptr, const char *to_append);

// 2
char	*ms_process_simple_var_expansion(const char *str, int i, \
				int *t_len, int d_pos);
char	*ms_process_curly_expansion(const char *str, int i, \
				int *t_len, int d_pos);

// 1
int		ms_process_one_expansion(const char *str, char **res_ptr, \
				int *cur_pos_ptr, int dol_pos, int status);
char	*ms_get_expansion_info(const char *str, int dollar_pos, \
				int *target_len);
int		ms_process_one_expansion(const char *str, char **res_ptr, \
				int *cur_pos_ptr, int dol_pos, int status);
char	*ms_expand_str_help(const char *original_str, int last_exit_status);
void	ms_expand_variables(char **args, int last_exit_status);

// --- built-ins ---
int		ms_execute_cd(char **args);
int		ms_execute_echo(char **args);
int		ms_execute_env(char **args, char **envp);
int		ms_execute_exit(char **args);
int		ms_execute_export(char **args, t_minishell *data);
int		ms_execute_pwd(char **args);
int		ms_execute_unset(char **args, t_minishell *data);

// --- exec ---
char	*ms_find_command_path(const char *cmd, char **envp);
int		ms_execute_external_command(char **args, char **envp);

#endif