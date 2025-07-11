/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:17:52 by goteixei          #+#    #+#             */
/*   Updated: 2025/01/05 18:00:44 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_putchar_fd
** 
** Prototype
** void ft_putchar_fd(char c, int fd);
** 
** Turn in files
** -
** 
** Parameters
** c: The character to output.
** fd: The file descriptor on which to write.
** 
** Return value
** None
** 
** External functs.
** write
**
** Description Outputs the character ’c’ to the given file
** descriptor.
*/

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
#include <stdio.h>

int main() {
    ft_putchar_fd('A', 1);

    fflush(stdout);

    ft_putchar_fd('B', 2);

    ft_putchar_fd('\n', 1);

    return 0;
}
*/
