/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:31:46 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 10:47:04 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a string is a valid POSIX identifier.
 *        Starts with '_' or an alphabet char.
 *        Contains only '_', alphabet chars, or digits.
 * @param str The string to check.
 * @return 1 if valid, 0 otherwise.
 * 
 * is alnum - alphanumeric
 */
static int	ms_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Prints the unset error message for an invalid identifier.
 * @param arg The invalid identifier string.
*/
static void	ms_print_invalid_identifier_err(const char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/**
 * @brief Finds the index of an environment variable in the list.
 *        Matches 'name=' at the beginning of an entry.
 * @param name The variable name to search for.
 * @param env_list The NULL-terminated environment list.
 * @return The index if found, -1 otherwise.
*/
static int	ms_find_env_var_index(const char *name, char **env_list)
{
	int		i;
	size_t	name_len;

	if (!name || !env_list)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (env_list[i])
	{
		if (ft_strncmp(env_list[i], name, name_len) == 0
			&& env_list[i][name_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief Removes an environment variable at a specific index in-place.
 *        Frees the string at the index and shifts subsequent pointers left.
 * @param index The index of the variable to remove.
 * @param data The main data structure containing the environ_list.
 * 
 * 1. Free the string ("KEY=VALUE") being removed
 * 2. Shift all subsequent pointers one position down (left)
 * 3. Set the last valid position (which now holds a duplicated pointer)
 *  to NULL to properly terminate the list.
*/
static void	ms_remove_env_var_at_index(int index, t_minishell *data)
{
	int	i;

	free(data->envp[index]);
	data->envp[index] = NULL;
	i = index;
	while (data->envp[i + 1])
	{
		data->envp[i] = data->envp[i + 1];
		i++;
	}
	data->envp[i] = NULL;
}

/**
 * @brief Executes the unset builtin command.
 *        Removes specified environment variables.
 * @param args Command arguments (args[0] is "unset").
 * @param data The main data structure containing the environ_list.
 * @return Exit status: 0 on success, 1 if any identifier was invalid.
*/
int	ms_execute_unset(char **args, t_minishell *data)
{
	int		i;
	int		exit_status;
	int		var_index;
	char	*var_name;

	exit_status = 0;
	i = 1;
	while (args[i])
	{
		var_name = args[i];
		if (!ms_valid_identifier(var_name))
		{
			ms_print_invalid_identifier_err(var_name);
			exit_status = 1;
		}
		else
		{
			var_index = ms_find_env_var_index(var_name, data->envp);
			if (var_index != -1)
				ms_remove_env_var_at_index(var_index, data);
		}
		i++;
	}
	return (exit_status);
}
