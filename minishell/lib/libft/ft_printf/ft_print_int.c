/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:31:20 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/15 16:31:09 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbr_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_put_int(int n)
{
	static char	digits[] = "0123456789";

	if (n > 9)
		ft_put_int(n / 10);
	write(1, (&digits[n % 10]), 1);
}

int	ft_print_int(int n)
{
	int	len;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	len = ft_nbr_len(n);
	if (n < 0)
	{
		write(1, "-", 1);
		n *= -1;
	}
	ft_put_int(n);
	return (len);
}

/*
#include <stdio.h>

int main(void)
{
	int test_number = -1;
	printf("Print result: \n");
	printf("Result length:\n%d", ft_print_int(test_number));
	printf("\n");
	return (0);
}
*/
