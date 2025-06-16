/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cd_setenv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:05:23 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/16 19:11:08 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Formats a variable name and value into a "NAME=value" string.
 * @param name The variable name (e.g., "PWD").
 * @param value The value to assign (e.g., "/home/user").
 * @return A newly allocated string (e.g., "PWD=/home/user"), or NULL on failure.
 */
static char	*ms_format_env_var(const char *name, const char *value)
{
	char	*name_with_equal;
	char	*full_entry;

	name_with_equal = ft_strjoin(name, "=");
	if (!name_with_equal)
	{
		perror("minishell: setenv (strjoin)");
		return (NULL);
	}
	full_entry = ft_strjoin(name_with_equal, value);
	free(name_with_equal);
	if (!full_entry)
	{
		perror("minishell: setenv (strjoin)");
		return (NULL);
	}
	return (full_entry);
}

/**
 * @brief Finds the index of an environment variable in your shell's envp list.
 * @param data The main shell data structure.
 * @param name The variable name to find.
 * @return The index of the variable if found, otherwise -1.
 */
static int	ms_find_env_var_index(t_minishell *data, const char *name)
{
	int		i;
	size_t	name_len;

	if (!data || !data->envp || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name, name_len) == 0
			&& data->envp[i][name_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

/**
 * @brief Adds a new variable to the environment list.
 *        This requires reallocating the entire envp array.
 * @param data The main shell data structure.
 * @param new_entry_str The full "NAME=value" string to add.
 * @return 0 on success, 1 on failure.
 * 
 * Allocate space for all old pointers, the new one, and the final NULL
 * Copy old pointers to the new array
 * NULL-terminate the new array
 * Free the OLD array of pointers, but not the strings it pointed to
 * Point the shell's data to the new, bigger array
 */
static int	ms_add_new_variable(t_minishell *data, const char *new_entry_str)
{
	int		current_count;
	char	**new_envp;
	int		i;

	current_count = 0;
	while (data->envp && data->envp[current_count])
		current_count++;
	new_envp = malloc(sizeof(char *) * (current_count + 2));
	if (!new_envp)
		return (perror("minishell: setenv (malloc)"), 1);
	i = 0;
	while (i < current_count)
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	new_envp[current_count] = ft_strdup(new_entry_str);
	if (!new_envp[current_count])
	{
		perror("minishell: setenv (strdup)");
		free(new_envp);
		return (1);
	}
	new_envp[current_count + 1] = NULL;
	if (data->envp)
		free(data->envp);
	data->envp = new_envp;
	return (0);
}

/**
 * @brief Sets or updates an environment variable in the shell's internal list.
 *        This function correctly handles both updating existing variables and
 *        adding new ones by reallocating the environment array.
 *
 * @param data The main shell data structure.
 * @param name The name of the variable to set (e.g., "PWD").
 * @param value The value to assign (e.g., "/home/user/newdir").
 * @return 0 on success, 1 on allocation failure.
 * 
 * If value is NULL, treat it as an empty string for consistency
 * --- Case 1: Variable exists, so update it ---
 * --- Case 2: Variable does not exist, so add it ---
 * The string is now owned by the new envp array, so we don't free it here
 */
int	ms_setenv(t_minishell *data, const char *name, const char *value)
{
	int		var_index;
	char	*new_entry_str;

	if (!data || !name)
		return (1);
	if (!value)
		value = "";
	var_index = ms_find_env_var_index(data, name);
	new_entry_str = ms_format_env_var(name, value);
	if (!new_entry_str)
		return (1);
	if (var_index != -1)
	{
		free(data->envp[var_index]);
		data->envp[var_index] = new_entry_str;
	}
	else
	{
		if (ms_add_new_variable(data, new_entry_str) != 0)
		{
			free(new_entry_str);
			return (1);
		}

		free(new_entry_str);
	}
	return (0);
}
