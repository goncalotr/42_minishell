/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 16:03:35 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Extracts the variable name from an argument string (e.g., "VAR=val").
 */
char	*ms_extract_var_name(const char *arg, size_t *len_name)
{
	char	*equal_sign;
	char	*name;

	if (!arg)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		*len_name = equal_sign - arg;
	else
		*len_name = ft_strlen(arg);
	name = (char *)malloc(sizeof(char) * (*len_name + 1));
	if (!name)
	{
		perror("minishell: export (malloc)");
		return (NULL);
	}
	ft_strlcpy(name, arg, *len_name + 1);
	return (name);
}

/**
 * @brief Handles adding a variable that does not yet exist.
 */
static int	ms_add_var(t_minishell *data, const char *arg, const char *name)
{
	char	*name_with_equals;

	if (ft_strchr(arg, '='))
		return (ms_add_new_env_var(data, arg));
	else
	{
		name_with_equals = ft_strjoin(name, "=");
		if (!name_with_equals)
		{
			perror("minishell: export (strjoin)");
			return (1);
		}
		if (ms_add_new_env_var(data, name_with_equals) != 0)
		{
			free(name_with_equals);
			return (1);
		}
		free(name_with_equals);
		return (0);
	}
}

/**
 * @brief Decides whether to add a new variable or update an existing one.
 */
int	ms_add_or_update_env_var(t_minishell *data, const char *arg)
{
	char	*name;
	size_t	name_len;
	int		index;

	name = ms_extract_var_name(arg, &name_len);
	if (!name)
		return (1);
	index = ms_find_env_var_index(name, name_len, data->envp);
	free(name);
	if (index != -1)
	{
		if (ft_strchr(arg, '='))
			return (ms_update_existing_env_var(data, index, arg));
		return (0);
	}
	else
		return (ms_add_var(data, arg, name));
}
