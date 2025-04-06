/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/06 17:28:40 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../inc/minishell.h"

// Definition of the global variable
int	g_last_exit_status = 0;

void	ms_core_loop(void)
{
	printf("ms_core_loop");
}

int	main(int argc, char **argv, char **envp)
{
	int test1 = argc;
	char **test2 = argv;
	char **test3 = envp;

	(void)test1;
	(void)test2;
	(void)test3;

	printf("Welcome to Minishell!\n");

	ms_core_loop();

	printf("Exiting Minishell. Final status: %d\n", g_last_exit_status);

	return (0);
}

