/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:07 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 16:35:36 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * read after $
 * search env vars
 * if found read after =
 * rewrite string
 * 
 * 
 * expansions
 * $VAR
 * ${VAR}
*/

//TODO quotes "" and ''

/**
 * @brief Determines what needs expanding starting at '$' and its length.
 *
 * @param str The full input string.
 * @param d_pos Index where '$' was found (using 'd_pos' for brevity).
 * @param t_len Pointer to store the length of the target sequence
 * (e.g., "$?" is 2).
 * @return An allocated string containing the info
 * ("?", "VAR_NAME", "$") or NULL on error.
 * 
 * Cases
 * 1 basic checks and $ at end of string
 * 2 $?
 * 3 $$
 * 4 { }
 * 5 normal case - is valid var -> mode 0,
 * 6 else '$' followed by invalid char -> trat $ literally
 * 
 */
char	*ms_get_expansion_info(const char *str, int dollar_pos, int *target_len)
{
	int		i;
	char	*info;

	i = dollar_pos + 1;
	*target_len = 1;
	info = NULL;
	if (!str || dollar_pos < 0 || str[dollar_pos] != '$' || str[i] == '\0')
		info = ft_strdup("$");
	else if (str[i] == '?')
	{
		*target_len = 2;
		info = ft_strdup("?");
	}
	else if (str[i] == '$')
	{
		*target_len = 2;
		info = ft_strdup("$$");
	}
	else if (str[i] == '{')
		info = ms_process_curly_expansion(str, i + 1, target_len, dollar_pos);
	else if (ms_valid_var(str[i], 0))
		info = ms_process_simple_var_expansion(str, i, target_len, dollar_pos);
	else
		info = ft_strdup("$");
	return (info);
}

/**
 * @brief Processes one potential expansion segment within the
 * main expansion loop.
 *        Appends literal part, gets info, gets value, appends value.
 *
 * @param str The original input string.
 * @param res_ptr Pointer to the result string pointer (modified).
 * @param cur_pos_ptr Pointer to the current position in 'str' (modified).
 * @param dol_pos The position of the current '$'.
 * @param status The last exit status for $?.
 * @return 0 on success, 1 on error.
 */
int	ms_process_one_expansion(const char *str, char **res_ptr, \
									int *cur_pos_ptr, int dol_pos, int status)
{
	char	*info;
	char	*value;
	char	*literal;
	int		target_len;

	target_len = 0;
	literal = ft_substr(str, *cur_pos_ptr, dol_pos - *cur_pos_ptr);
	if (!literal || ms_append_and_free(res_ptr, literal))
	{
		free(literal);
		return (1);
	}
	free(literal);
	info = ms_get_expansion_info(str, dol_pos, &target_len);
	if (!info)
		return (1);
	value = ms_get_expansion_value(info, status);
	free(info);
	if (!value)
		return (1);
	if (ms_append_and_free(res_ptr, value))
		return (free(value), 1);
	free(value);
	*cur_pos_ptr = dol_pos + target_len;
	return (0);
}

/**
 * @brief Expands variables in a string using helper functions.
 *        !TODO QUOTES
 *
 * @param original_str The string to expand.
 * @param last_exit_status The exit status for $?.
 * @return A newly allocated expanded string, or NULL on error.
 */
char	*ms_expand_str_help(const char *original_str, int last_exit_status)
{
	char	*result;
	char	*literal_part;
	int		current_pos;
	int		dollar_pos;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	current_pos = 0;
	dollar_pos = -1;
	dollar_pos = ms_find_next_dollar(original_str, current_pos);
	while (dollar_pos != -1)
	{
		if (ms_process_one_expansion(original_str, &result, &current_pos,
				dollar_pos, last_exit_status) != 0)
			return (free(result), NULL);
		dollar_pos = ms_find_next_dollar(original_str, current_pos);
	}
	literal_part = ft_substr(original_str, current_pos,
			ft_strlen(original_str) - current_pos);
	if (!literal_part || ms_append_and_free(&result, literal_part))
		return (free(literal_part), free(result), NULL);
	return (free(literal_part), result);
}

/**
 * @brief Iterates through args array and expands variables in each argument
 *        using the helper-based expansion. Ignores quotes.
 *
 * @param args The argument array (from ft_split). Will be modified.
 * @param last_exit_status The value for $?.
 */
void	ms_expand_variables(char **args, int last_exit_status)
{
	int		i;
	char	*expanded_arg;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			expanded_arg = ms_expand_str_help(args[i], last_exit_status);
			if (!expanded_arg)
				ms_expand_error(args, i, 1);
			else
			{
				free(args[i]);
				args[i] = expanded_arg;
			}
		}
		i++;
	}
}
