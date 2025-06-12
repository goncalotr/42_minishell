/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:44:33 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 15:12:29 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_putnbr_fd
** 
** Prototype
** void ft_putnbr_fd(int n, int fd);
** 
** Turn in files
** -
** 
** Parameters
** n: The integer to output.
** fd: The file descriptor on which to write.
** 
** Return value
** None
** 
** External functs.
** write
** 
** Description
** Outputs the integer ’n’ to the given file
** descriptor.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	last_number;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	last_number = (n % 10) + '0';
	write(fd, &last_number, 1);
}

/*
#include <stdio.h>

int main() {
    printf("Testing ft_putnbr_fd with positive integer:\n");
    ft_putnbr_fd(12345, 1);
    write(1, "\n", 1);

    printf("Testing ft_putnbr_fd with negative integer:\n");
    ft_putnbr_fd(-6789, 1);
    write(1, "\n", 1);

    printf("Testing ft_putnbr_fd with zero:\n");
    ft_putnbr_fd(0, 1);
    write(1, "\n", 1);

    printf("Testing ft_putnbr_fd with minimum integer:\n");
    ft_putnbr_fd(-2147483648, 1);
    write(1, "\n", 1);

    return 0;
}
*/
