/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_placeholder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:04:12 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/07 18:32:15 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Frees the memory allocated for a NULL-terminated string array
 *        (like one returned by ft_split).
 * @param args The string array to free.
 */
void	ms_free_split_args(char **args)
{
	int	i;

	if (!args)
		return;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * @brief VERY basic placeholder parser using ft_split.
 * Splits the input line by spaces. Does NOT handle quotes, etc.
 * @param input_line The raw input line from readline.
 * @return A NULL-terminated array of strings (arguments), or NULL on failure.
 */
char	**ms_parse_input_placeholder(const char *input_line)
{
	char	**args;

	// NOTE: This split is NOT robust (doesn't handle quotes, etc.)
	// Replace with real tokenizer/parser later.
	args = ft_split(input_line, ' '); // Assumes ft_split exists
	if (!args)
	{
		perror("minishell: placeholder parser (ft_split) failed");
		// Don't free input_line here, the caller (main) still owns it
		return (NULL); // Signal failure
	}
	return (args);
}

int	ms_execute_command_placeholder(char **args)
{
	// Check if parser produced at least one arg
	if (args == NULL || args[0] == NULL)
	{
		return (0); // No command entered (e.g., just spaces), success (status 0)
	}

	// --- Builtin Dispatch ---
	// Check for "cd"
	// Use ft_strcmp if required by norminette/project rules

	// cd
	if (strcmp(args[0], "cd") == 0)
	{
		return (ms_execute_cd(args)); // Return status from cd function
	}

	// echo
	// env
	// exit
	// export

	// pwd
	else if (strcmp(args[0], "pwd") == 0)
	{
		return (ms_execute_pwd(args)); // Call the new pwd function
	}

	//unset

	// Add checks for other builtins here (pwd, echo, etc.)
	// else if (strcmp(args[0], "pwd") == 0)
	// {
	//     return (ms_execute_pwd(args));
	// }
	// ...

	// --- If not a known builtin ---
	else
	{
		// Placeholder for External Commands / Command Not Found
		// TODO: Implement fork/execve for non-builtins later
		ft_putstr_fd("minishell: command not found: ", 2); // Assumes ft_putstr_fd
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		return (127); // Standard "command not found" exit code
	}
}
