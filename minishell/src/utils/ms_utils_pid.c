/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 01:54:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/27 20:24:37 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../inc/minishell.h"

/**
 * exit()
*/
int	ms_getpid(void)
{
	pid_t	child_pid;
	pid_t	presumed_parent_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (child_pid == 0)
	{
		exit(0);
	}
	presumed_parent_pid = child_pid - 1;
	waitpid(child_pid, NULL, 0);
	return (presumed_parent_pid);
}
