/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <jpedro-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:47:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/19 14:04:15 by jpedro-f         ###   ########.fr       */
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
# include <fcntl.h>
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
#include <termios.h>

// non-standard librarys
# include "../lib/libft/libft.h"

/**************************************************************************
 * SECTION: Macros
 **************************************************************************/

// --- ANSI Color Codes ---
# define RESET   "\001\033[0m\002"
# define BLACK   "\001\033[0;30m\002"
# define RED     "\001\033[0;31m\002"
# define GREEN   "\001\033[0;32m\002"
# define YELLOW  "\001\033[0;33m\002"
# define BLUE    "\001\033[0;34m\002"
# define MAGENTA "\001\033[0;35m\002"
# define CYAN    "\001\033[0;36m\002"
# define WHITE   "\001\033[0;37m\002"

// using PATH_MAX from limits.h (4096)
//# define PATH_MAX 1000

/**************************************************************************
 * SECTION: Structs
 **************************************************************************/

typedef enum e_token_type
{
	TOKEN_INFILE,				// 0 infile
	TOKEN_OUTFILE,				// 1 outfile
	TOKEN_CMD,					// 2 commands
	TOKEN_PIPE,					// 3 |
	TOKEN_REDIR_IN,				// 4 <
	TOKEN_REDIR_OUT,			// 5 >
	TOKEN_APPEND,				// 6 >>
	TOKEN_HEREDOC,				// 7 <<
	TOKEN_EOF,					// 8 end of file
}	t_token_type;

typedef enum e_token_state
{
	GENERAL,					// 0 normal
	DOUBLE_QUOTES,				// 1 ""
	SIMPLE_QUOTES,				// 2 ''
}	t_token_state;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	t_token_state			state;
	char					**args;
	bool					expand;
	int						*expand_index;
	struct s_token			*previous;
	struct s_token			*next;
}	t_token;

typedef struct s_ast
{
	t_token_type	type;
	char			**args;
	int				node_nbr;
	char			*file_name;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

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
	char	**paths;
	int		last_exit_status;
	t_token	*token_list;
	t_ast	*tree;
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
	char	*shell_name;
	char	**envp_orig;
}	t_minishell;

extern volatile sig_atomic_t	g_signal;

/**************************************************************************
 * SECTION: Functions
 **************************************************************************/

// --- main ---
//void	ms_core_loop(char **envp);
//int	main(int argc, char **argv, char **envp);	

// --- prompt ---
char	*ms_get_prompt(t_minishell *data);

// --- debug ---
void	ms_debug_print_args(char **args);
void	ms_debug_print_gsig(void);

// --- init ---
int		init_shell_data(t_minishell *data, char **argv, char **envp);

// --- signals ---
void	ms_signal_handlers_init(void);
void	ms_signal_handlers_set_interactive(void);

// ------------------PARSER-------------------------
// ms_syntax_check.c
bool	ms_unclosed_quotes(char *input);
bool	ms_syntax_check(char *input);
bool 	ms_syntax_check2(char *input_line);
bool	ms_pipes_placement(char *input);
bool	ms_rediractions_placement(char *input);


//ms_syntax_utils.c
char	*ms_remove_whitespaces(char *input_line);
void	ms_skip_inside_quotes(int *i, char *input);
void	ms_skip_whitespaces(int *i, char *input);
bool 	ms_not_required (char *input);

// ms_list_utils.c
t_token	*ms_last_node(t_token *list);
t_token	*ms_append_node(t_token *list, char *input, t_token_type type);
void	ms_print_tokens(t_token *list);

//ms_tokenization.c
int		ms_len_token(char *input, int i);
char	*ms_cpy_token(char *input, int *i);
char	*ms_cpy_token_cmd(char *input, int *i);
t_token *ms_start_tokenization(char *input, t_token *list);
t_token	*ms_tokenization(t_minishell *data, char *input);

//ms_tokenization_utils.c
t_token	*ms_extract_word(char *input, int *i, t_token *list);
t_token	*ms_extract_eof(t_token *list, char * input, int *i);
t_token *ms_extract_operator(char *input, int *i, t_token *list);
t_token	*ms_assign_state(t_token *list);

//ms_tokenization_utils2.c
bool	ms_is_quote(char c);
bool	ms_ismetachar(char c);
bool	ms_isspace(char c);
bool	ms_is_infile(t_token *list);
bool	ms_is_file(t_token	*list);

//ms_cleanup.c
void 	ms_clean_ast(t_ast *node);
void	ms_cleanup_shell(t_minishell *data);
void	ms_free_envp_copy(char **envp);
void	ms_free_data_paths(char **paths);
void	ms_clean_all(t_minishell *data);

//ms_quotes.c
int	ms_new_value_len(char *value);
char	*ms_put_new_value(char *value, char *new_value);
char	*ms_quotes_off(char *value);
t_token *ms_handle_quotes(t_token *list);

//ms_quotes_cmd.c
int	ms_len_args(char *value);
int	ms_len_arg(char *value, int *i);
char	 *ms_put_args(char *value,int *i);
t_token	*ms_quotes_cmd(t_token *token, int x);

//ms_expansion_check.c
int	*ms_expansion_index(char *value, int *index);
int ms_expansion_count(char *value);
void ms_expansion_search(t_token *list);
t_token	*ms_expansion_check(t_token *list);

// ms_main_parsing.c
void	ms_main_parsing(char *input, t_minishell *data);
void print_indent(int level);
const char *get_token_type_name(t_token_type type);
void print_ast(t_ast *node, int level);

// ms_parsing.c
t_ast	*ms_parse_command(t_token **token);
t_ast	*ms_create_file_node(t_token *token);
t_ast	*ms_parse_redirection(t_token	**token_list);
t_ast	*ms_parse_pipes(t_token **token_list);
t_ast 	*ms_parse_tokens(t_token	**token_list);

// ms_parsing_utils.c
t_ast	*ms_new_ast_node(t_token_type type);
t_ast	*ms_create_and_link_redir(t_token **token_list);
char	**ms_cpy_array(char **src);
void	ms_free_array(char **array);

// ms_tree_exec.c
int	ms_exec_tree(t_ast *node, t_minishell *data);
int	ms_exec_cmd(t_ast *node, t_minishell *data);
int	ms_exec_pipe(t_ast *node, t_minishell *data);
int	ms_exec_redir_in(t_ast *node, t_minishell *data);
int	ms_exec_redir_out(t_ast	*node, t_minishell *data);
void	ms_exec_heredoc(t_ast *node);

// ms_tree_exec_utils.c
void	ms_prepare_heredocs(t_ast *node);
void	ms_clean_heredocs(t_ast *node);
void	ms_command_not_found(char **cmds);

// parsing placeholder 
void	ms_free_split_args(char **args);
char	**ms_parse_input_placeholder(const char *input_line);
int		ms_execute_command_placeholder(char **args, t_minishell *data);


// --------------------------------------------------------------------


// --- expand ---

// utils
int		ms_valid_var(char c, int mode);
int		ms_expand_error(char **args, int i, int mode);
int		ms_find_next_dollar(const char *str, int start_pos);
int		ms_append_and_free(char **base_str_ptr, const char *to_append);

// 2
char	*ms_process_simple_var_expansion(const char *str, int i, \
				int *t_len, int d_pos);
char	*ms_process_curly_expansion(const char *str, int i, \
				int *t_len, int d_pos);
char	*ms_get_expansion_value(t_minishell *data, const char *info);

// 1
/*
//int		ms_process_one_expansion(const char *str, char **res_ptr, \
				int *cur_pos_ptr, int dol_pos, int status);
//char	*ms_get_expansion_info(const char *str, int dollar_pos, \
				int *target_len);
//int		ms_process_one_expansion(const char *str, char **res_ptr, \
				int *cur_pos_ptr, int dol_pos, int status);
//char	*ms_expand_str_help(const char *original_str, int last_exit_status);
*/
t_token	*ms_expand_variables(t_minishell *data, t_token *list_head);

// --- built-ins ---
int		ms_execute_cd(t_minishell *data, char **args);
int		ms_setenv(t_minishell *data, const char *name, const char *value);
int		ms_execute_echo(char **args);
int		ms_execute_env(char **args, char **envp);
int		ms_execute_exit(char **args, t_minishell *data);
void	ms_exit_shell(t_minishell *data, int exit_code);
int		ms_execute_export(char **args, t_minishell *data);
int		ms_execute_pwd(char **args);
int		ms_execute_unset(char **args, t_minishell *data);

// --- exec ---
char	*ms_find_command_path(const char *cmd, char **envp);
int		ms_execute_external_command(char **envp, char **args);

// --- utils ---
int		ms_exit_with_code(t_minishell *data, int status);
int		ms_getpid(void);

#endif