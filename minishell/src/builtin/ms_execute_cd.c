/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:32:46 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/07 17:58:25 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints an error message for cd to standard error.
 * @param msg The specific error message.
 * @param details Optional details (like the directory name). Can be NULL.
 * @return Always returns 1 (failure exit status for cd).
 */
static int	cd_error(char *msg, char *details)
{	
	//todo create ft_fprintf
	//fprintf(stderr, "minishell: cd: %s", msg);
	//if (details)
	//{
	//	fprintf(stderr, ": %s", details);
	//}
	//fprintf(stderr, "\n");
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(msg, 2);
	if (details)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(details, 2);
	}
	ft_putstr_fd(details, 2);
	return (1);
}

/**
 * @brief Executes the 'cd' built-in command.
 * Changes the current working directory. Handles 'cd' and 'cd <path>'.
 * Does NOT update PWD/OLDPWD environment variables in this simple version.
 * @param args Argument vector. args[0] is "cd", args[1] (optional) is 
 * the target directory.
 * @return 0 on success, 1 on failure.
 * 
 * Part 1: Check arguments
 * Part 2: Change directory
 */
int	ms_execute_cd(char **args)
{
	char	*target_dir;

	if (args[1] == NULL)
	{
		target_dir = getenv("HOME");
		if (target_dir == NULL)
			return (cd_error("HOME not set", NULL));
	}
	else
	{
		if (args[2] != NULL)
		{
			return (cd_error("too many arguments", NULL));
		}
		target_dir = args[1];
	}
	if (chdir(target_dir) == -1)
	{
		char error_prefix[1024];
		snprintf(error_prefix, sizeof(error_prefix), "minishell: cd: %s", \
		target_dir);
		perror(error_prefix);
		return (1);
	}
	//TODO PWD OLDPWD
	return (0);
}
