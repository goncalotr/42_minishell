/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:32:18 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 15:10:21 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_putendl_fd
** 
** Prototype
** void ft_putendl_fd(char *s, int fd);
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
** Outputs the string ’s’ to the given file descriptor
** followed by a newline.
*/

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

/*
#include <stdio.h>

int main()
{
    printf("Testing ft_putendl_fd with standard output:\n");
    ft_putendl_fd("asdsfsafsa", 1);

    printf("Testing ft_putendl_fd with standard error:\n");
    ft_putendl_fd("B", 2);

    printf("Testing ft_putendl_fd with newline:\n");
    ft_putendl_fd("\n", 1);

    printf("Testing NULL input:\n");
    ft_putendl_fd(NULL, 1);

    return 0;
}
*/
