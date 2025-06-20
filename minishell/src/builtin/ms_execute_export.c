/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:33:50 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 16:22:58 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Helper to check if a string is a valid shell identifier.
 */
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

/**
 * @brief Helper to print the standard "not a valid identifier" error.
 */
static void	ms_print_export_invalid_identifier_err(const char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	if (arg)
		ft_putstr_fd((char *)arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

/*
** @brief Validates an argument, extracts its name, and checks if it's empty.
** @return Returns the extracted variable name, or NULL if validation fails.
*/
static char	*ms_validate_and_extract_arg(char *arg, size_t *name_len)
{
	char	*var_name;

	var_name = ms_extract_var_name(arg, name_len);
	if (!var_name || *name_len == 0)
	{
		ms_print_export_invalid_identifier_err(arg);
		if (var_name)
			free(var_name);
		return (NULL);
	}
	return (var_name);
}

/**
 * @brief Main loop to process each argument given to the export command.
 */
static int	ms_process_export_args(t_minishell *data, char **args)
{
	int		i;
	int		exit_status;
	char	*var_name;
	size_t	name_len;

	exit_status = 0;
	i = 1;
	while (args[i])
	{
		var_name = ms_validate_and_extract_arg(args[i], &name_len);
		if (!var_name)
			exit_status = 1;
		else if (!ms_is_valid_identifier(var_name))
		{
			ms_print_export_invalid_identifier_err(args[i]);
			exit_status = 1;
		}
		else if (ms_add_or_update_env_var(data, args[i]) != 0)
			exit_status = 1;
		if (var_name)
			free(var_name);
		i++;
	}
	return (exit_status);
}

int	ms_execute_export(char **args, t_minishell *data)
{
	if (args[1] == NULL)
		return (ms_print_exported_vars(data));
	else
		return (ms_process_export_args(data, args));
}
