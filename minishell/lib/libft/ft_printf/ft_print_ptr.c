/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:00:55 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/15 16:31:03 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptr_len(unsigned long long n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len += 1;
		n /= 16;
	}
	return (len);
}

static void	ft_put_ptr(unsigned long long n)
{
	static char	hex[] = "0123456789abcdef";

	if (n >= 16)
	{
		ft_put_ptr(n / 16);
		ft_put_ptr(n % 16);
	}
	if (n < 16)
	{
		write(1, &hex[n], 1);
	}
}

int	ft_print_ptr(unsigned long long *ptr)
{
	int	len;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	len = ft_ptr_len((unsigned long long)ptr);
	write(1, "0x", 2);
	ft_put_ptr((unsigned long long) ptr);
	return (2 + len);
}
