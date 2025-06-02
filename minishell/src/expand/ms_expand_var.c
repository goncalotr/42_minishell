/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:07 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/02 23:22:15 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ms_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = start;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

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
static char	*ms_get_expansion_info(const char *str, int dollar_pos, int *target_len)
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
static int	ms_process_one_expansion(t_minishell *data, char *str, char **res_ptr, \
									int *cur_pos_ptr, int dol_pos)
{
	char	*info;
	char	*value;
	char	*literal;
	int		target_len;

	target_len = 0;
	literal = ft_substr(str, (unsigned int) *cur_pos_ptr, dol_pos - *cur_pos_ptr);
	if (!literal || ms_append_and_free(res_ptr, literal))
	{
		free(literal);
		return (1);
	}
	free(literal);
	info = ms_get_expansion_info(str, dol_pos, &target_len);
	if (!info)
		return (1);
	value = ms_get_expansion_value(data, str);
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
 * 
 * ! add last exit status from program struct
 */
/*
static char	*ms_expand_str_help(const char *original_str, int last_exit_status)
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
*/
static char	*ms_expand_str_help(t_minishell *data, t_token *list)
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
	dollar_pos = ms_find_next_dollar(list->value, current_pos);
	while (dollar_pos != -1)
	{
		if (ms_process_one_expansion(data, list->value, &result, &current_pos,
				dollar_pos) != 0)
			return (free(result), NULL);
		dollar_pos = ms_find_next_dollar(list->value, current_pos);
	}
	literal_part = ms_substr(list->value, current_pos,
			ft_strlen(list->value) - current_pos);
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
t_token *ms_expand_variables(t_minishell *data, t_token *list)
{
	//int		i;
	//char	*expanded_arg;
	//int		current_pos;
	t_token	*temp_token;
	char	*original_value;
	char	*expanded_value;

	if (!list)
		return (NULL);
	temp_token = list;
	if (!temp_token->value)
		return (NULL);

	//i = 0;
	while (temp_token)
	{
		// here doc
		// no expand, clean expand_index
		if (temp_token->type == TOKEN_EOF)
		{
			if (temp_token->expand_index)
			{
				free(temp_token->expand_index);
				temp_token->expand_index = NULL;
			}
			temp_token->expand = false;
			temp_token = temp_token->next;
			continue;
		}

		if (temp_token->expand == true && temp_token->value)
		{
			original_value = temp_token->value;
			expanded_value = ms_expand_str_help(data, temp_token);

			// result check
			if (!expanded_value)
			{
				ft_putstr_fd("minishell: expansion error for token value: ", \
STDERR_FILENO);
				ft_putendl_fd(original_value, STDERR_FILENO);
			}
			else
			{
				free(original_value);
				temp_token->value = expanded_value;
			}
		}

		// clean expand_index
		if (temp_token->expand_index)
		{
			free(temp_token->expand_index);
			temp_token->expand_index = NULL;
		}
		temp_token->expand = false;

		temp_token = temp_token->next;
	}
	return (list);
}
