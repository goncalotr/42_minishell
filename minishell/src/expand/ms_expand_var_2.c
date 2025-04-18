/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:58:28 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 15:39:36 by goteixei         ###   ########.fr       */
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
