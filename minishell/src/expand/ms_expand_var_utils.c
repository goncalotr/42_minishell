/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:54:06 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 15:30:36 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * mode 0 start - can't accept numbers
 * mode 1 after start - accept numbers
 */
int	ms_valid_var(char c, int mode)
{
	if (mode == 0)
	{
		if (isalpha(c) || c == '_')
		{
			return (true);
		}
	}
	else if (mode == 1)
	{
		if (isalnum(c) || c == '_')
		{
			return (true);
		}
	}
	return (false);
}

/**
 * print error
 * ft_putstr_fd(args[i] ? args[i] : "(null)", 2);
 */
int	ms_expand_error(char **args, int i, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd("minishell: expansion memory error for arg: ", 2);
		if (args[i])
			ft_putstr_fd(args[i], 2);
		else
			ft_putstr_fd("(null)", 2);
		ft_putstr_fd("\n", 2);
	}
	return (0);
}

/**
 * @brief Finds the index of the next '$' in 'str' at or after 'start_pos'.
 * @return Index of '$' or -1 if not found.
 */
int	ms_find_next_dollar(const char *str, int start_pos)
{
	const char	*dollar_ptr;

	if (!str || start_pos < 0 || (size_t)start_pos >= ft_strlen(str))
		return (-1);
	dollar_ptr = ft_strchr(str + start_pos, '$');
	if (dollar_ptr)
		return (dollar_ptr - str);
	return (-1);
}

/**
 * @brief Gets the expanded value for the given info.
 *
 * @param info The info string ("?", "VAR_NAME", "$").
 * @param last_exit_status The exit status for $?.
 * @return An allocated string with the value, or NULL on memory error.
 */
char	*ms_get_expansion_value(const char *info, int last_exit_status)
{
	char	*env_val;

	if (!info)
		return (NULL);
	if (strcmp(info, "?") == 0)
	{
		return (ft_itoa(last_exit_status));
	}
	else if (strcmp(info, "$") == 0)
	{
		return (ft_strdup("$"));
	}
	else
	{
		env_val = getenv(info);
		if (env_val)
			return (ft_strdup(env_val));
		else
			return (ft_strdup(""));
	}
}

/**
 * @brief Helper to append strings, freeing the old base string.
 * Assumes ft_strjoin allocates new memory.
 * @return 0 on success, 1 on error.
 */
int	ms_append_and_free(char **base_str_ptr, const char *to_append)
{
	char	*old;
	char	*new;

	if (!base_str_ptr || !*base_str_ptr || !to_append)
		return (1);
	old = *base_str_ptr;
	new = ft_strjoin(old, to_append);
	free(old);
	if (!new)
	{
		base_str_ptr = NULL;
		return (1);
	}
	*base_str_ptr = new;
	return (0);
}
