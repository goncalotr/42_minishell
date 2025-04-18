/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug_global_signal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:18:29 by goteixei          #+#    #+#             */
/*   Updated: 2025/04/18 18:23:07 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern unsigned char	g_signal;

void	ms_debug_print_gsig(void) {

	ft_printf(YELLOW "DEBUG g_signal = %d\n" RESET, (unsigned int)g_signal);
}
