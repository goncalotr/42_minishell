/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_getenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:09:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 13:28:59 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Searches for an environment variable in the shell's internal list.
 * @param data The main shell data structure.
 * @param name The name of the variable to find (e.g., "HOME").
 * @return A pointer to the value part of the string if found
 *         (e.g., "/home/goteixei"), or NULL if the variable is not found.
 *         NOTE: This function returns a pointer
 *         to existing memory within data->envp.
 *         Do NOT free the returned pointer.
 */
char	*ms_getenv(t_minishell *data, const char *name)
{
	int		i;
	size_t	name_len;

	if (!data || !data->envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name, name_len) == 0
			&& data->envp[i][name_len] == '=')
		{
			return (data->envp[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}
