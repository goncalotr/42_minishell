/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:42:20 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 17:36:14 by goteixei         ###   ########.fr       */
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
		return (*base_ptr = NULL, \
			ft_putstr_fd("minishell: prompt build allocation error\n", \
			2), 1);
	*base_ptr = new_base;
	return (0);
}

static char	*ms_build_fallback_prompt(void)
{
	char	*prompt;

	prompt = ft_strdup(BLUE);
	if (prompt && ms_build_str_append(&prompt, "minishell") != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, BLACK) != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, "> ") != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, RESET) != 0)
	{
	}
	if (!prompt)
		ft_putstr_fd("minishell: prompt allocation error (fallback)\n", 2);
	return (prompt);
}

/**
* @brief Builds the main dynamic part of the prompt string.
*        Format: BLUE "user@pwd" color "> " RESET
* @param user The username string.
* @param pwd The current directory string.
* @param color The color string (e.g., GREEN or RED) for '>'.
* @return Allocated string or NULL on failure.
*/
static char	*ms_build_dynamic_prompt(const char *user, const char *pwd, \
	const char *color)
{
	char	*prompt;

	prompt = ft_strdup(BLUE);
	if (prompt && ms_build_str_append(&prompt, user) != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, "@") != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, pwd) != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, color) != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, "> ") != 0)
	{
	}
	if (prompt && ms_build_str_append(&prompt, RESET) != 0)
	{
	}
	return (prompt);
}

/**
 * @brief Generates the prompt string dynamically.
 *
 * Format: BLUE "USERNAME@DIR" WHITE "> " RESET
 * Fallback: BLUE "minishell" WHITE "> " RESET
 * @return A newly allocated string containing the prompt, or NULL on error.
 *         The caller is responsible for freeing the returned string.
 * 
 * non zero staus represents error
 */
char	*ms_get_prompt(int last_status)
{
	char		*user;
	char		*pwd;
	const char	*prompt_color;

	if (last_status == 0)
	{
		prompt_color = GREEN;
	}
	else
	{
		prompt_color = RED;
	}
	user = getenv("USER");
	pwd = getenv("PWD");
	if (!user || !pwd)
		return (ms_build_fallback_prompt());
	return (ms_build_dynamic_prompt(user, pwd, prompt_color));
}
