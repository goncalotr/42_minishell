/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:33:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/18 20:16:54 by goteixei         ###   ########.fr       */
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
// Check if the entry starts with "name="
static int	ms_find_env_var_index(const char *name, size_t name_len, \
		char **env_list)
{
	int	i;

	i = 0;
	if (!name || !env_list)
		return (-1);
	while (env_list[i])
	{
		if (ft_strncmp(env_list[i], name, name_len) == 0 \
			&& env_list[i][name_len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

// Prints the "not a valid identifier" error message for export.
static void	ms_print_export_invalid_identifier_err(const char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

// Extracts the variable name part from an export argument (e.g., "VAR=" -> "VAR").
// Returns an allocated string for the name, or NULL on allocation failure or if arg is NULL.
// Also sets name_len via the pointer.
static char	*ms_extract_var_name(const char *arg, size_t *len_name)
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

// Needed by add_or_update_env_var
static int	ms_add_new_env_var(t_minishell *data, const char *new_var_str)
{
	int		count = 0;
	char	**new_environ;
	char	*var_copy;
	int		i;

	if (data->envp) {
		while (data->envp[count])
			count++;
	}
	new_environ = (char **)malloc(sizeof(char *) * (count + 2));
	if (!new_environ) {
		perror("minishell: export: malloc error for new env list");
		return (1);
	}
	i = 0;
	while (i < count)
	{
		new_environ[i] = data->envp[i];
		i++;
	}
	var_copy = ft_strdup(new_var_str);
	if (!var_copy) {
		perror("minishell: export: ft_strdup error for new var");
		free(new_environ);
		return (1);
	}
	new_environ[count] = var_copy;
	new_environ[count + 1] = NULL;
	if (data->envp) {
		free(data->envp);
	}
	data->envp = new_environ;
	return (0);
}

// Needed by add_or_update_env_var
static int	ms_update_existing_env_var(t_minishell *data, int index, const char *new_var_str)
{
	char *var_copy;

	var_copy = ft_strdup(new_var_str);
	if (!var_copy) {
		perror("minishell: export: ft_strdup error updating var");
		return (1);
	}
	free(data->envp[index]);
	data->envp[index] = var_copy;
	return (0);
}

// Definition for the function causing the second error
// arg is "NAME=value" or "NAME"

//status = ms_update_existing_env_var(data, index, arg);
// "export NAME=new_value" - update it
// "export NAME" and NAME already exists. Mark for export (Bash), or no-op.

// Variable "NAME" does not exist
// "export NAME=value"
// "export NAME" (and NAME does not exist) - add as "NAME=" to expand to empty
static int	ms_add_or_update_env_var(t_minishell *data, const char *arg)
{
	char	*name;
	size_t	name_len;
	int		index;
	int		status;

	name = ms_extract_var_name(arg, &name_len);
	if (!name)
		return (1);
	if (!ms_is_valid_identifier(name))
	{
		ms_print_export_invalid_identifier_err(arg);
		free(name);
		return (1);
	}
	index = ms_find_env_var_index(name, name_len, data->envp);
	if (index != -1) {
		if (ft_strchr(arg, '='))
			status = ms_update_existing_env_var(data, index, arg);
		else
			status = 0;
	}
	else
	{
		if (ft_strchr(arg, '='))
			status = ms_add_new_env_var(data, arg);
		else
		{ 
			char *name_with_equals = ft_strjoin(name, "=");
			if (!name_with_equals)
			{
				perror("minishell: export: ft_strjoin");
				status = 1;
			}
			else
			{
				status = ms_add_new_env_var(data, name_with_equals);
				free(name_with_equals);
			}
		}
	}
	free(name);
	return (status);
}

// BUBBLE SORT 
static int	ms_print_exported_vars(t_minishell *data)
{
	int		i;
	int		j;
	int		count;
	char	**env_copy = NULL;
	char	*temp;
	char	*value_ptr;

	i = 0;
	j = 0;
	count = 0;
	if (data->envp)
	{
		while (data->envp[count])
			count++;
	}
	if (count == 0)
		return (0);
	env_copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
	{
		perror("minishell: export: malloc error for env copy");
		return (1);
	}
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(data->envp[i]);
		if (!env_copy[i])
		{
			perror("minishell: export: ft_strdup error for env copy entry");
			while (--i >= 0) free(env_copy[i]);
			free(env_copy);
			return (1);
		}
		i++;
	}
	env_copy[count] = NULL;
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < count - i -1)
		{
			if (strcmp(env_copy[j], env_copy[j + 1]) > 0)
			{
				temp = env_copy[j];
				env_copy[j] = env_copy[j + 1];
				env_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		value_ptr = ft_strchr(env_copy[i], '=');
		if (value_ptr)
		{
			write(STDOUT_FILENO, env_copy[i], value_ptr - env_copy[i]);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			char *val = value_ptr + 1;
			while(*val) {
				if (*val == '"' || *val == '$' || *val == '\\')
					ft_putchar_fd('\\', STDOUT_FILENO);
				ft_putchar_fd(*val, STDOUT_FILENO);
				val++;
			}
			ft_putstr_fd("\"", STDOUT_FILENO);
		} else
			ft_putstr_fd(env_copy[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	i = 0;
	while (i < count)
	{
		free(env_copy[i]);
		i++;
	}
	free(env_copy);
	return (0);
}

/**
 * @brief Exports variables to the environment or prints exported variables.
 * @param args Command arguments, args[0] = "export", args[1..n] = assignments.
 * @param data Pointer to the main shell data structure.
 * @return int 0 on success, 1 if any identifier was invalid or allocation failed.
 * 
 * 1 Export with no arguments
 * 2 Export with arguments
 */
int	ms_execute_export(char **args, t_minishell *data)
{
	int			i;
	int			exit_status;
	char		*var_name;
	size_t		name_len;
	int			op_status;

	exit_status = 0;
	i = 1;
	if (args[i] == NULL)
		return (ms_print_exported_vars(data));
	while (args[i])
	{
		var_name = ms_extract_var_name(args[i], &name_len);
		if (!var_name || name_len == 0)
		{
			ms_print_export_invalid_identifier_err(args[i]);
			exit_status = 1;
			if (var_name)
				free(var_name);
			i++;
			continue;
		}
		if (!ms_is_valid_identifier(var_name))
		{
			ms_print_export_invalid_identifier_err(args[i]);
			exit_status = 1;
		}
		else
		{
			op_status = ms_add_or_update_env_var(data, args[i]);
			if (op_status != 0)
				exit_status = 1;
		}
		free(var_name);
		i++;
	}
	return (exit_status);
}

