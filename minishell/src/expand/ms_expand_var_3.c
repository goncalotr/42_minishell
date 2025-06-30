/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_var_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:21:22 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 15:05:59 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ms_handle_special_info_cases(const char *str, int i, \
int *target_len)
{
	if (str[i] == '?')
	{
		*target_len = 2;
		return (ft_strdup("?"));
	}
	if (str[i] == '0')
	{
		*target_len = 2;
		return (ft_strdup("0"));
	}
	if (str[i] == '$')
	{
		*target_len = 2;
		return (ft_strdup("$$"));
	}
	return (NULL);
}

char	*ms_get_expansion_info(const char *str,
	int dollar_pos, int *target_len)
{
	int		i;
	char	*info;

	i = dollar_pos + 1;
	*target_len = 1;
	if (!str || dollar_pos < 0 || str[dollar_pos] != '$' || str[i] == '\0')
		return (ft_strdup("$"));
	info = ms_handle_special_info_cases(str, i, target_len);
	if (info)
		return (info);
	if (str[i] == '{')
		info = ms_process_curly_expansion(str, i + 1, target_len, dollar_pos);
	else if (ms_valid_var(str[i], 0))
		info = ms_process_simple_var_expansion(str, i, target_len, dollar_pos);
	else
		info = ft_strdup("$");
	return (info);
}

/**
 * given string starts with $
 * returns the expanded value of that $ construct.
 * updates 'construct_len_ptr' with the length of the recognized construct 
 */
char	*ms_process_dollar_construct(t_minishell *data, \
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
