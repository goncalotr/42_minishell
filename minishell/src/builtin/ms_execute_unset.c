/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:31:46 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/14 18:09:00 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Helper to check if a string is a valid environment variable name.
// POSIX: Starts with letter or underscore, contains letters, numbers, underscores.
// Returns 1 if valid, 0 otherwise.
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

// Helper to print the "not a valid identifier" error message.
// Cast needed if arg is const
static void ms_print_invalid_identifier_err(const char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

// Finds the index of the environment variable 'name' in 'env_list'.
// Returns the index if found, or -1 if not found.
// Check if the entry starts with "name="
static int ms_find_env_var_index(const char *name, char **env_list)
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

// Removes the environment variable at the specified index by shifting pointers.
// Assumes 'index' is valid and within bounds.
static void ms_remove_env_var_at_index(int index, t_data *data)
{
	int i;

	// Free the string memory of the variable being removed
	free(data->environ_list[index]);
	data->environ_list[index] = NULL; // Optional: clear the pointer early

	// Shift all subsequent pointers one position up
	i = index;
	while (data->environ_list[i + 1]) // Stop before the NULL terminator
	{
		data->environ_list[i] = data->environ_list[i + 1];
		i++;
	}
	// The last non-NULL pointer is now moved up, effectively removing the gap.
	// Set the now-last position to NULL, correctly terminating the list.
	data->environ_list[i] = NULL;

	// Note: This does not shrink the allocated memory for the char** array itself.
	// For many unsets, this could lead to wasted pointer space, but it's simpler
	// than reallocating the array frequently.
}

int		ms_execute_unset(char **args, t_data *data)
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
			var_index = ms_find_env_var_index(var_name, data->environ_list);
			if (var_index != -1)
			{
				ms_remove_env_var_at_index(var_index, data);
			}
		}
		i++;
	}
	return (exit_status);
}
