/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:58:28 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 13:11:25 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Helper for get_expansion_info to handle the $VAR case.
 *
 * @param str The full input string.
 * @param i Index position after the '$'.
 * @param t_len Pointer to update with the target length
 * (from '$' to end of name).
 * @param d_pos Index of the original '$'.
 * @return Allocated string with variable name, or NULL on malloc error.
 */
char	*ms_process_simple_var_expansion(const char *str, int i, \
		int *t_len, int d_pos)
{
	int		name_len;	
	char	*info_str;

	name_len = 0;
	while (ms_valid_var(str[i + name_len], 1))
		name_len++;
	*t_len = (i + name_len) - d_pos;
	info_str = ft_substr(str, i, name_len);
	return (info_str);
}

/**
 * @brief Helper for get_expansion_info to handle the ${VAR} case.
 *
 * @param str The full input string.
 * @param i Index position after the '{'.
 * @param t_len Pointer to update with the target length (from '$' to '}').
 * @param d_pos Index of the original '$'.
 * @return Allocated string with variable name,
 * or "$" if syntax error, or NULL on malloc error.
 * 
 * find }
 * extract name
 * no closing } -> treat $ literally 
 */
char	*ms_process_curly_expansion(const char *str, int i, \
		int *t_len, int d_pos)
{
	int		name_len;
	char	*info_str;

	name_len = 0;
	while (str[i + name_len] && str[i + name_len] != '}')
	{
		name_len++;
	}
	if (str[i + name_len] == '}')
	{
		*t_len = (i + name_len + 1) - d_pos;
		info_str = ft_substr(str, i, name_len);
	}
	else
	{
		*t_len = 1;
		info_str = ft_strdup("$");
	}
	return (info_str);
}

/**
 * @brief Gets the expanded value for the given info.
 *
 * @param info The info string ("?", "VAR_NAME", "$").
 * @param last_exit_status The exit status for $?.
 * @return An allocated string with the value, or NULL on memory error.
 * 
 * 1 Error
 * 2 $?
 * 3 $$
 * 4 literal $
 * 5 $VAR adn ${VAR}
 */
char	*ms_get_expansion_value(t_minishell *data, const char *info)
{
	char	*env_val;
	pid_t	pid;

	if (!info)
		return (NULL);
	if (ft_strcmp(info, "?") == 0)
		return (ft_itoa(data->last_exit_status));
	else if (ft_strcmp(info, "$$") == 0)
	{
		pid = getpid();
		pid = ms_getpid();
		return (ft_itoa((int)pid));
	}
	else if (ft_strcmp(info, "$") == 0)
		return (ft_strdup("$"));
	else
	{
		env_val = ms_getenv(data, info);
		if (env_val)
			return (ft_strdup(env_val));
		else
			return (ft_strdup(""));
	}
}
