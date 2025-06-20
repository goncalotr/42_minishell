/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:32:46 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/20 13:22:43 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ms_cd_error(const char *arg, const char *msg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

static int	update_pwd_vars(t_minishell *data)
{
	char	cwd_buffer[PATH_MAX];
	char	*old_pwd_val;

	old_pwd_val = ms_getenv(data, "PWD");
	if (old_pwd_val)
	{
		ms_setenv(data, "OLDPWD", old_pwd_val);
	}
	if (getcwd(cwd_buffer, sizeof(cwd_buffer)) != NULL)
	{
		ms_setenv(data, "PWD", cwd_buffer);
	}
	else
	{
		perror("minishell: cd: getcwd error");
		return (1);
	}
	return (0);
}

/**
 * @brief Executes the 'cd' built-in command.
 * Changes the current working directory. Handles 'cd' and 'cd <path>'.
 * Does NOT update PWD/OLDPWD environment variables in this simple version.
 * @param args Argument vector. args[0] is "cd", args[1] (optional) is 
 * the target directory.
 * @return 0 on success, 1 on failure.
 * 
 * Part 1: Check arguments and define target dir
 * to many args
 * cd and cd ~
 * cd -
 * cd something
 * Part 2: Change directory
 * 
 * 
 */
int	ms_execute_cd(t_minishell *data, char **args)
{
	char	*target_dir;

	if (args[1] && args[2])
		return (ms_cd_error(NULL, "too many arguments"));
	if (args[1] == NULL || ft_strcmp(args[1], "~") == 0)
	{
		target_dir = ms_getenv(data, "HOME");
		if (target_dir == NULL)
			return (ms_cd_error("HOME not set", NULL));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target_dir = ms_getenv(data, "OLDPWD");
		if (target_dir == NULL)
			return (ms_cd_error("OLDPWD not set", NULL));
		ft_putendl_fd(target_dir, STDOUT_FILENO);
	}
	else
	{
		target_dir = args[1];
	}
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(target_dir);
		return (1);
	}
	update_pwd_vars(data);
	return (0);
}
