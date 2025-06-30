/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:07 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 11:28:06 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//static char	*ms_expand_and_remove_quotes(t_minishell *data, const char *value);
/*
static char	*ms_get_expansion_info(const char *str, \
int dollar_pos, int *target_len);
static char	*ms_process_dollar_construct(t_minishell *data, \
const char *str_starting_with_dollar, int *construct_len_ptr);
static char	*ms_char_append(char *str, char c);
*/

/*
static char	*ms_char_append(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len + 2);
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(new_str, str, len);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	free(str);
	return (new_str);
}
*/

/**
 * @brief Expands variables and removes quotes in a single pass.
 * This is the core of the fix. It iterates through the token's value,
 * maintaining a quote state to correctly handle expansion and literal chars.
 *
 * @param data The main shell data structure.
 * @param value The original string value of the token.
 * @return A new, fully processed string with variables expanded and
 *         quotes removed.
 */
/*
static char	*ms_expand_and_remove_quotes(t_minishell *data, const char *value)
{
	char			*result;
	t_token_state	state;
	int				i;
	char			*expanded_value;
	int				construct_len;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	state = GENERAL;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && state == GENERAL)
			state = SIMPLE_QUOTES;
		else if (value[i] == '\'' && state == SIMPLE_QUOTES)
			state = GENERAL;
		else if (value[i] == '"' && state == GENERAL)
			state = DOUBLE_QUOTES;
		else if (value[i] == '"' && state == DOUBLE_QUOTES)
			state = GENERAL;
		else if (value[i] == '$' && state != SIMPLE_QUOTES)
		{
			expanded_value = ms_process_dollar_construct(data, \
				&value[i], &construct_len);
			if (!expanded_value)
			{
				free(result);
				return (NULL);
			}
			if (ms_append_and_free(&result, expanded_value))
			{
				free(expanded_value);
				free(result);
				return (NULL);
			}
			free(expanded_value);
			i += construct_len;
			continue ;
		}
		else
		{
			result = ms_char_append(result, value[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}
*/

/*
static char	*ms_expand_variables_in_string(t_minishell *data, const char *value)
{
	char			*result;
	t_token_state	state;
	int				i;
	char			*expanded_value;
	int				construct_len;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	state = GENERAL; // We still use state to know if we are inside single quotes
	i = 0;
	while (value[i])
	{
		// Toggle state but DON'T skip the character
		if (value[i] == '\'' && state == GENERAL)
			state = SIMPLE_QUOTES;
		else if (value[i] == '\'' && state == SIMPLE_QUOTES)
			state = GENERAL;
		
		// Handle expansion only if not in single quotes
		if (value[i] == '$' && state != SIMPLE_QUOTES)
		{
			// This part is the same as before
			expanded_value = ms_process_dollar_construct(data, &value[i], &construct_len);
			if (!expanded_value)
			{
				free(result);
				return (NULL);
			}
			if (ms_append_and_free(&result, expanded_value))
			{
				free(expanded_value);
				free(result);
				return (NULL);
			}
			free(expanded_value);
			i += construct_len; // Move past the processed construct (e.g., "$VAR")
			continue ;
		}
		
		// Append the current character to the result
		result = ms_char_append(result, value[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
*/

/*
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
*/

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

static char	*ms_get_expansion_info(const char *str, \
int dollar_pos, int *target_len)
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
/*
static int	ms_process_one_expansion(t_minishell *data, \
char *str, char **res_ptr, int *cur_pos_ptr, int dol_pos)
{
	char	*info;
	char	*value;
	char	*literal;
	int		target_len;

	target_len = 0;
	literal = ms_substr(str, (unsigned int) *cur_pos_ptr, \
	dol_pos - *cur_pos_ptr);
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
*/

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
/*
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
*/

/**
 * given string starts with $
 * returns the expanded value of that $ construct.
 * updates 'construct_len_ptr' with the length of the recognized construct 
 */
static char	*ms_process_dollar_construct(t_minishell *data, \
const char *str_starting_with_dollar, int *construct_len_ptr)
{
	char	*info;
	char	*value;

	*construct_len_ptr = 0;
	info = ms_get_expansion_info(str_starting_with_dollar, 0, \
		construct_len_ptr);
	if (!info)
	{
		if (construct_len_ptr && *construct_len_ptr == 0)
			*construct_len_ptr = 1;
		return (ft_strdup("$"));
	}
	value = ms_get_expansion_value(data, info);
	free(info);
	if (!value)
	{
		if (construct_len_ptr && *construct_len_ptr == 0)
			*construct_len_ptr = 1;
		return (NULL);
	}
	return (value);
}

/**
 * 
 */
/*
static char	*ms_substr_2(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	k;
	size_t	s_len_val;

	if (s == NULL)
		return (NULL);
	s_len_val = ft_strlen(s);
	if (start >= s_len_val)
		return (ft_strdup(""));
	if (len > s_len_val - start)
		len = s_len_val - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	k = 0;
	while (k < len)
	{
		substr[k] = s[start + k];
		k++;
	}
	substr[k] = '\0';
	return (substr);
}
*/

/**
 * char	*result_str;				// The final expanded string being built
 * char	*literal_prefix;			// Literal part before a '$'
 * char	*expanded_value;			// Value from ms_process_dollar_construct
 * int	current_pos_in_token;		// Our scan
 * 									   position in token_to_expand->value
 * int	dollar_pos;					// Position of the next '$' found
 * int	processed_construct_len;	// Length of the $VAR construct processed
 */
/*
static char	*ms_expand_str_help(t_minishell *data, t_token *token_to_expand)
{
	char	*result_str;
	char	*literal_prefix;
	char	*expanded_value;
	int		current_pos_in_token;
	int		dollar_pos;
	int		processed_construct_len;

	if (!token_to_expand || !token_to_expand->value)
		return (ft_strdup(""));
	result_str = ft_strdup("");
	if (!result_str)
		return (NULL);
	current_pos_in_token = 0;
	while ((size_t)current_pos_in_token < ft_strlen(token_to_expand->value))
	{
		dollar_pos = ms_find_next_dollar(token_to_expand->value, \
		current_pos_in_token);
		if (dollar_pos == -1)
		{
			literal_prefix = ms_substr_2(token_to_expand->value, \
			current_pos_in_token, \
			ft_strlen(token_to_expand->value) - current_pos_in_token);
			if (!literal_prefix)
			{
				if (result_str)
					free(result_str);
				return (NULL);
			}
			if (ms_append_and_free(&result_str, literal_prefix))
			{
				free(literal_prefix);
				if (result_str)
					free(result_str);
				return (NULL);
			}
			free(literal_prefix);
			break ;
		}
		else
		{
			if (dollar_pos > current_pos_in_token)
			{
				literal_prefix = ms_substr_2(token_to_expand->value, \
					current_pos_in_token, dollar_pos - current_pos_in_token);
				if (!literal_prefix)
				{
					if (result_str)
						free(result_str);
					return (NULL);
				}
				if (ms_append_and_free(&result_str, literal_prefix))
				{
					if (result_str)
						free(result_str);
					return (NULL);
				}
				free(literal_prefix);
			}
			expanded_value = ms_process_dollar_construct(data, \
				token_to_expand->value + dollar_pos, &processed_construct_len);
			if (!expanded_value)
			{
				if (result_str)
					free(result_str);
				return (NULL);
			}
			if (ms_append_and_free(&result_str, expanded_value))
			{
				free(expanded_value);
				if (result_str)
					free(result_str);
				return (NULL);
			}
			free(expanded_value);
			current_pos_in_token = dollar_pos + processed_construct_len;
		}
	}
	return (result_str);
}
*/

/**
 * @brief Iterates through args array and expands variables in each argument
 *        using the helper-based expansion. Ignores quotes.
 *
 * @param args The argument array (from ft_split). Will be modified.
 * @param last_exit_status The value for $?.
 */
/*
t_token	*ms_expand_variables(t_minishell *data, t_token *list_head)
{
	t_token	*current_token;
	char	*original_value;
	char	*expanded_value_str;

	if (!list_head)
		return (NULL);
	current_token = list_head;
	if (!current_token->value)
		return (NULL);
	while (current_token)
	{
		if (current_token->type == TOKEN_EOF)
		{
			if (current_token->expand_index)
			{
				free(current_token->expand_index);
				current_token->expand_index = NULL;
			}
			current_token->expand = false;
			current_token = current_token->next;
			continue ;
		}
		if (current_token->expand == true && current_token->value)
		{
			original_value = current_token->value;
			expanded_value_str = ms_expand_str_help(data, current_token);
			if (!expanded_value_str)
			{
				ft_putstr_fd("minishell: expansion error for token value: ", \
STDERR_FILENO);
				ft_putendl_fd(original_value, STDERR_FILENO);
			}
			else
			{
				free(original_value);
				current_token->value = expanded_value_str;
			}
		}
		if (current_token->expand_index)
		{
			free(current_token->expand_index);
			current_token->expand_index = NULL;
		}
		current_token->expand = false;
		current_token = current_token->next;
	}
	return (list_head);
}
*/

/**
 * @brief Builds a new string by expanding variables at specified indices.
 * @return A new, expanded string, or NULL on error.
 */
/*
static char *ms_expand_str_with_indices(t_minishell *data, t_token *token)
{
	char	*result_str;
	char	*literal_part;
	char	*expanded_value;
	int		current_pos;
	int		i;
	int		dollar_pos;
	int		construct_len;

	result_str = ft_strdup("");
	if (!result_str) return (NULL);

	current_pos = 0;
	i = 0;
	while (token->expand_index[i] != -1)
	{
		dollar_pos = token->expand_index[i];

		// 1. Append the literal part before the '$'
		if (dollar_pos > current_pos)
		{
			literal_part = ft_substr(token->value, current_pos, dollar_pos - current_pos);
			ms_append_and_free(&result_str, literal_part);
			free(literal_part);
		}

		// 2. Get the expanded value
		expanded_value = ms_process_dollar_construct(data, &token->value[dollar_pos], &construct_len);
		if (!expanded_value)
			return (free(result_str), NULL);
		ms_append_and_free(&result_str, expanded_value);
		free(expanded_value);

		// 3. Update the current position to be after the processed construct
		current_pos = dollar_pos + construct_len;
		i++;
	}

	// Append any remaining literal part after the last expansion
	if ((size_t)current_pos < ft_strlen(token->value))
	{
		literal_part = ft_substr(token->value, current_pos, ft_strlen(token->value) - current_pos);
		ms_append_and_free(&result_str, literal_part);
		free(literal_part);
	}

	return (result_str);
}
*/

/**
 * @brief Scans a string from left to right and expands variables in a single pass.
 * @param data    The main shell data structure for accessing environment variables.
 * @param value   The original string from the token to be expanded.
 * @return        A new, fully expanded string, or NULL on memory allocation failure.
 * 
 * find the next $
 * case a: no more dollar signs
 * case b: dollar sign is found
 * literal text is appended to result str
 * ms_process_dollar_construct - processes the expansion
 * expanded value is appended to result_str
 * current_pos goes past the entire construct (dollar_pos + construct_len)
 * in order to prevent re-expanding
 * loop repeats from current_pos
 */
static char *ms_expand_string_scanner(t_minishell *data, const char *value)
{
	char *result_str;
	char *literal_part;
	char *expanded_value;
	int current_pos;
	int dollar_pos;
	int construct_len;

	result_str = ft_strdup("");
	if (!result_str)
		return (NULL);
	current_pos = 0;
	while (value[current_pos] != '\0')
	{
		dollar_pos = ms_find_next_dollar(value, current_pos);
		if (dollar_pos == -1)
		{
			literal_part = ft_substr(value, current_pos, ft_strlen(value) - current_pos);
			ms_append_and_free(&result_str, literal_part);
			free(literal_part);
			break;
		}
		if (dollar_pos > current_pos)
		{
			literal_part = ft_substr(value, current_pos, dollar_pos - current_pos);
			ms_append_and_free(&result_str, literal_part);
			free(literal_part);
		}
		expanded_value = ms_process_dollar_construct(data, &value[dollar_pos], &construct_len);
		if (!expanded_value)
			return (free(result_str), NULL);
		ms_append_and_free(&result_str, expanded_value);
		free(expanded_value);
		current_pos = dollar_pos + construct_len;
	}
	return (result_str);
}

/**
 * @brief Iterates through the token list and applies
 *        expansion and quote removal.
 *        This version uses the new, combined function
 *        for correctness.
 *
 * @param data The main shell data structure.
 * @param list_head The head of the token list.
 * @return The (potentially modified) head of the token list.
 */
t_token	*ms_expand_variables(t_minishell *data, t_token *list_head)
{
	t_token		*current_token;
	char		*original_value;
	char		*expanded_value_str;

	current_token = list_head;
	while (current_token)
	{
		if (current_token->expand == true && current_token->value)
		{
			original_value = current_token->value;
			expanded_value_str = ms_expand_string_scanner(data, original_value);
			if (!expanded_value_str)
				ft_putstr_fd("minishell: expansion error\n", 2);
			else
			{
				current_token->value = expanded_value_str;
				free(original_value);
			}
		}
		if (current_token == current_token->next)
		{
			free(current_token->expand_index);
			current_token->expand_index = NULL;
		}
		current_token = current_token->next;
	}
	return (list_head);
}
