/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:42:20 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 16:54:51 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_build_str_append(char **base_ptr, const char *to_append)
{
	char	*old_base;
	char	*new_base;

	if (!base_ptr || !to_append)
		return (1);
	if (!*base_ptr)
	{
		*base_ptr = ft_strdup(to_append);
		if (!*base_ptr)
		{
			ft_putstr_fd("minishell: prompt build allocation error\n", 2);
			return (1);
		}
		return (0);
	}
	old_base = *base_ptr;
	new_base = ft_strjoin(old_base, to_append);
	free(old_base);
	if (!new_base)
	{
		*base_ptr = NULL;
		ft_putstr_fd("minishell: prompt build allocation error\n", 2);
		return (1);
	}
	*base_ptr = new_base;
	return (0);
}

/**
 * @brief Generates the prompt string dynamically.
 *
 * Format: BLUE "USERNAME@DIR" WHITE "> " RESET
 * Fallback: BLUE "minishell" WHITE "> " RESET
 * @return A newly allocated string containing the prompt, or NULL on error.
 *         The caller is responsible for freeing the returned string.
 */
char *ms_get_prompt(void)
{
	char	*user;
	char	*pwd;
	char	*prompt;

	user = getenv("USER");
	pwd = getenv("PWD");
	if (!user || !pwd)
	{
		prompt = ft_strdup(BLUE "minishell" BLACK "> " RESET);
		if (!prompt)
			ft_putstr_fd("minishell: prompt allocation error\n", 2);
		return (prompt);
	}
	prompt = ft_strdup(BLUE);
	if (prompt && ms_build_str_append(&prompt, user) != 0) {}
	if (prompt && ms_build_str_append(&prompt, "@") != 0) {}
	if (prompt && ms_build_str_append(&prompt, pwd) != 0) {}
	if (prompt && ms_build_str_append(&prompt, BLACK) != 0) {}
	if (prompt && ms_build_str_append(&prompt, "> ") != 0) {}
	if (prompt && ms_build_str_append(&prompt, RESET) != 0) {}
	if (!prompt)
		ft_putstr_fd("minishell: failed to construct dynamic prompt\n", 2);
	return (prompt);
}
