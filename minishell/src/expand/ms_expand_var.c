/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:23:07 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 13:21:56 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_process_and_append_expansion(t_minishell *data, \
const char *value, char **result_ptr, int *current_pos)
{
	char	*literal;
	char	*expanded;
	int		dollar_pos;
	int		construct_len;

	dollar_pos = ms_find_next_dollar(value, *current_pos);
	if (dollar_pos == -1)
	{
		literal = ft_substr(value, *current_pos, ft_strlen(value));
		if (ms_append_and_free(result_ptr, literal))
			return (free(literal), 1);
		return (free(literal), 2);
	}
	if (dollar_pos > *current_pos)
	{
		literal = ft_substr(value, *current_pos, dollar_pos - *current_pos);
		if (ms_append_and_free(result_ptr, literal))
			return (free(literal), 1);
		free(literal);
	}
	expanded = ms_process_dollar_construct(data, &value[dollar_pos],
			&construct_len);
	if (!expanded || ms_append_and_free(result_ptr, expanded))
		return (free(expanded), 1);
	return (free(expanded), *current_pos = dollar_pos + construct_len, 0);
}

/**
 * @brief Scans a string from left to right and expands variables
 * in a single pass.
 * @param data    The main shell data structure for accessing
 * environment variables.
 * @param value   The original string from the token to be expanded.
 * @return        A new, fully expanded string, or NULL on memory
 * allocation failure.
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
static char	*ms_expand_string_scanner(t_minishell *data, const char *value)
{
	char	*result_str;
	int		current_pos;
	int		status;

	result_str = ft_strdup("");
	if (!result_str)
		return (NULL);
	current_pos = 0;
	while (value[current_pos] != '\0')
	{
		status = ms_process_and_append_expansion(data, value,
				&result_str, &current_pos);
		if (status == 1)
			return (free(result_str), NULL);
		if (status == 2)
			break ;
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
			free(current_token->expand_index);
		current_token->expand_index = NULL;
		current_token = current_token->next;
	}
	return (list_head);
}
