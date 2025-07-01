/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_export_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 12:44:45 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 12:45:45 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_extract_var_name(const char *arg, size_t *len_name)
{
	char	*equal_sign;
	char	*name;

	if (!arg)
		return (NULL);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		if (equal_sign > arg && *(equal_sign - 1) == '+')
			*len_name = (equal_sign - 1) - arg;
		else
			*len_name = equal_sign - arg;
	}
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
 * @brief Private helper to find a variable's index for export.
 */
int	ms_find_var_index(const char *name, size_t len, char **env_list)
{
	int	i;

	i = 0;
	if (!name || !env_list)
		return (-1);
	while (env_list[i])
	{
		if (ft_strncmp(env_list[i], name, len) == 0
			&& env_list[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Private helper to update a variable at a given index.
 */
int	ms_update_var(t_minishell *data, int index, const char *new_str)
{
	char	*var_copy;

	var_copy = ft_strdup(new_str);
	if (!var_copy)
	{
		perror("minishell: export (strdup)");
		return (1);
	}
	free(data->envp[index]);
	data->envp[index] = var_copy;
	return (0);
}
