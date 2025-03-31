# Minishell Function Prefixes

This document outlines the function prefixes used in the Minishell project for code organization and clarity.

**Minishell specific functions names start with the prefix `ms_`.**

**Note:** The `ft_` prefix is reserved for functions from your `libft` library.  It should *not* be used for Minishell-specific functions.

## Prefixes

!TODO
<!---
 Table still needs review
-->

| Prefix         | Description                                      | Example Function(s)                                                                   | File(s)          |
|----------------|--------------------------------------------------|--------------------------------------------------------------------------------------|-------------------|
| `ms_`          | Main/Minishell - Overall shell operations.       | `ms_init()`, `ms_mainloop()`, `ms_cleanup()`, `ms_prompt()`                          | `main.c`          |
| `ms_lexer_`    | Lexical Analysis - Tokenizing the input.        | `ms_lexer_tokenize()`, `ms_lexer_add_token()`, `ms_lexer_print_tokens()`              | `ms_lexer.c`      |
| `ms_parser_`   | Parsing - Building the Abstract Syntax Tree (AST). | `ms_parser_build_ast()`, `ms_parser_parse_command()`, `ms_parser_parse_pipeline()`, `ms_parser_parse_redirection()`, `ms_parser_create_node()` | `ms_parser.c`     |
| `ms_ast_`      | AST Manipulation - Operations on the AST.        | `ms_ast_free()`, `ms_ast_print()`, `ms_ast_find_node()`                                | `ms_ast.c`        |
| `ms_expand_`   | Expansion - Variable, quote, and tilde expansion. | `ms_expand_variables()`, `ms_expand_quotes()`, `ms_expand_tilde()`, `ms_expand_command()` | `ms_expand.c`   |
| `ms_exec_`     | Execution - Command execution and process management. | `ms_exec_command()`, `ms_exec_builtin()`, `ms_exec_external()`, `ms_exec_pipeline()`, `ms_exec_redirection()` | `ms_exec.c`      |
| `ms_builtin_`  | Built-in Commands - Implementation of builtins.    | `ms_builtin_cd()`, `ms_builtin_echo()`, `ms_builtin_exit()`, `ms_builtin_export()`, ...| `ms_builtin_*.c`  |
| `ms_signal_`   | Signal Handling - Signal management.              | `ms_signal_init()`, `ms_signal_handler()`                                                | `ms_signal.c`     |
| `ms_error_`    | Error Handling - Error reporting and handling.     | `ms_error_print()`, `ms_error_exit()`, `ms_error_set()`                                 | `ms_error.c`      |
| `ms_utils_`    | Utilities - General helper functions.             | `ms_utils_safe_malloc()`, `ms_utils_strdup()`, `ms_utils_strjoin()`, `ms_utils_is_valid_var_name()`  | `ms_utils.c`     |
| `ft_` *        | Libft - Functions from the libft library.       |  *(Various libft functions)*                                                              | `libft/*`      |
