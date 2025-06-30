/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:59 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 12:45:24 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Private helper to add a new variable by reallocating the env list.
 */
static int	ms_add_new_var(t_minishell *data, const char *new_str)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	if (data->envp)
		while (data->envp[count])
			count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (perror("minishell: export (malloc)"), 1);
	i = 0;
	while (i < count)
	{
		new_env[i] = data->envp[i];
		i++;
	}
	new_env[count] = ft_strdup(new_str);
	if (!new_env[count])
		return (free(new_env), perror("minishell: export (strdup)"), 1);
	new_env[count + 1] = NULL;
	if (data->envp)
		free(data->envp);
	data->envp = new_env;
	return (0);
}

/**
 * @brief Handles adding a variable that does not yet exist.
 */
static int	ms_add_var_logic(t_minishell *data, const char *arg, \
const char *name)
{
	char	*name_with_equals;

	if (ft_strchr(arg, '='))
		return (ms_add_new_var(data, arg));
	else
	{
		name_with_equals = ft_strjoin(name, "=");
		if (!name_with_equals)
		{
			perror("minishell: export (strjoin)");
			return (1);
		}
		if (ms_add_new_var(data, name_with_equals) != 0)
		{
			free(name_with_equals);
			return (1);
		}
		free(name_with_equals);
		return (0);
	}
}

int	ms_add_or_update_env_var(t_minishell *data, const char *arg)
{
	char	*name;
	size_t	name_len;
	int		index;
	int		status;

	name = ms_extract_var_name(arg, &name_len);
	if (!name)
		return (1);
	index = ms_find_var_index(name, name_len, data->envp);
	if (index != -1)
	{
		status = 0;
		if (ft_strchr(arg, '='))
			status = ms_update_var(data, index, arg);
	}
	else
		status = ms_add_var_logic(data, arg, name);
	free(name);
	return (status);
}
