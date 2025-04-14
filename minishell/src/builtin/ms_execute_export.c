/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:33:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/14 18:48:05 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//todo needs linkedlist?

//todo repeat function, merge them and send it to utils
static int	ms_is_valid_identifier(const char *str)
{
	int	i;

	if (!str || str[0] == '\0' || (!ft_isalpha(str[0]) && str[0] != '_'))
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

//todo find_env_var_index (reuse or copy from unset)
static int find_env_var_index(const char *name, size_t name_len, char **env_list)
{
	int i = 0;
	if (!name || !env_list)
		return (-1);

	while (env_list[i])
	{
		// Check if the entry starts with "name="
		if (ft_strncmp(env_list[i], name, name_len) == 0
			&& env_list[i][name_len] == '=')
		{
			return (i); // Found it
		}
		i++;
	}
	return (-1); // Not found
}

// Prints the "not a valid identifier" error message for export.
static void print_export_invalid_identifier_err(const char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO); // Cast needed if arg is const
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

// Extracts the variable name part from an export argument (e.g., "VAR=" -> "VAR").
// Returns an allocated string for the name, or NULL on allocation failure or if arg is NULL.
// Also sets name_len via the pointer.
static char *extract_var_name(const char *arg, size_t *len_name)
{
	char *equal_sign;
	char *name;

	if (!arg) return (NULL);

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		*len_name = equal_sign - arg;
	else
		*len_name = ft_strlen(arg);
	name = (char *)malloc(sizeof(char) * (*len_name + 1));
	if (!name)
	{
		perror("minishell: export: malloc error extracting name");
		return (NULL);
	}
	ft_strlcpy(name, arg, *len_name + 1);
	name[*len_name] = '\0';
	return (name);
}

/**
 * @brief Executes the export builtin command.
 *
 * Adds/updates variables in the environment or lists them.
 * Manages the environment via a pointer to the envp array.
 *
 * @param args Arguments array (args[0] is "export").
 * @param envp_ptr Pointer to the shell's environment array pointer.
 * @return int 0 on success, 1 if any identifier was invalid.
 */
/*
int ms_execute_export(char **args, char ***envp_ptr)
{
	int	i;
	int	ret_status;

	return (ret_status);
}
*/
