/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:26:25 by goteixei          #+#    #+#             */
/*   Updated: 2025/01/05 18:04:40 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_putstr_fd
** 
** Prototype
** void ft_putstr_fd(char *s, int fd);
** 
** Turn in files
** -
** 
** Parameters
** s: The string to output.
** fd: The file descriptor on which to write.
** 
** Return value
** None
** 
** External functs.
** write
** 
** Description
** Outputs the string ’s’ to the given file
** descriptor.
*/

#include "libft.h"

void	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

/*
#include <stdio.h>

int main()
{
    ft_putstr_fd("asdsfsafsa", 1);

    fflush(stdout);

    ft_putstr_fd("", 2);

    ft_putstr_fd("\n", 1);

    printf("Testing NULL input:\n");
    ft_putstr_fd(NULL, 1);

    return 0;
}
*/
