/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:42:20 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 15:06:50 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief we could print the entire path or in this case just
 * the current directory name
 * 
 * get prompt
 * root directory
 * search for last slash
 * the function ends with safe fallback that shouldn't happen with absolute
 * paths
 */
static char	*ms_get_current_path(void)
{
	char		*full_path;
	const char	*dir_name_ptr;
	char		*last_slash;
	char		*result_name;

	full_path = getcwd(NULL, 0);
	if (!full_path)
		return (NULL);
	if (strcmp(full_path, "/") == 0)
		dir_name_ptr = "/";
	else
	{
		last_slash = ft_strrchr(full_path, '/');
		if (last_slash != NULL)
			dir_name_ptr = last_slash + 1;
		else
			dir_name_ptr = full_path;
	}
	result_name = ft_strdup(dir_name_ptr);
	free(full_path);
	if (!result_name)
		return (ft_putstr_fd("minishell: directory name allocation error\n", \
2), NULL);
	return (result_name);
}

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

static char	*ms_build_fallback_prompt(const char *color)
{
	char	*prompt;

	prompt = ft_strdup(BLUE);
	if (prompt && ms_build_str_append(&prompt, "minishell") != 0)
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
char	*ms_get_prompt(t_minishell *data)
{
	char		*user;
	char		*dir_name;
	char		*prompt;
	const char	*prompt_color;

	if (data->last_exit_status == 0)
		prompt_color = GREEN;
	else
		prompt_color = RED;
	user = getenv("USER");
	dir_name = ms_get_current_path();
	if (!user || !dir_name)
	{
		if (dir_name)
			free(dir_name);
		return (ms_build_fallback_prompt(prompt_color));
	}
	prompt = ms_build_dynamic_prompt(user, dir_name, prompt_color);
	free(dir_name);
	if (!prompt)
	{
		ft_putstr_fd("minishell: prompt build allocation error\n", 2);
		return (ms_build_fallback_prompt(prompt_color));
	}
	return (prompt);
}
