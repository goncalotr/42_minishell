/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_placeholder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:04:12 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 10:56:44 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int g_last_exit_status;

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

int	ms_execute_command_placeholder(char **args, t_minishell *data)
{
	if (args == NULL || args[0] == NULL)
		return (0);
	if (strcmp(args[0], "cd") == 0)
		return (ms_execute_cd(args));
	if (strcmp(args[0], "echo") == 0)
		return (ms_execute_echo(args));
	if (strcmp(args[0], "env") == 0)
		return (ms_execute_env(args, data->envp));
	if (strcmp(args[0], "exit") == 0)
		return (ms_execute_exit(args));
	if (strcmp(args[0], "export") == 0)
		return ms_execute_export(args, data);
	else if (strcmp(args[0], "pwd") == 0)
		return (ms_execute_pwd(args));
	else if (strcmp(args[0], "unset") == 0)
		return (ms_execute_unset((args), data));
	else
		return (ms_execute_external_command(args, data->envp));
}
