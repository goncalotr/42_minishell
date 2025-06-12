/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:07:59 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/15 16:31:18 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_len(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

static void	ft_put_hex(unsigned int nbr, const char format)
{
	int	len;

	len = 0;
	if (nbr >= 16)
	{
		ft_put_hex(nbr / 16, format);
		ft_put_hex(nbr % 16, format);
	}
	if (nbr < 16)
	{
		if (format == 'x')
			len += write(1, &"0123456789abcdef"[nbr], 1);
		if (format == 'X')
			len += write(1, &"0123456789ABCDEF"[nbr], 1);
	}
}

int	ft_print_hex(unsigned int nbr, const char format)
{
	if (nbr == 0)
	{
		return (write(1, "0", 1));
	}
	else
		ft_put_hex(nbr, format);
	return (ft_hex_len(nbr));
}

/*
#include <stdio.h>

int main(void)
{
	int	len_original;
	int	len_new;

	len_original = 0;
	len_new = 0;

	printf("\nTEST x\n");
	printf("Testing: (\"\\tThe hex number %%x is visible.\\n\", 4242)\n");
	len_original += printf("Original: \tthe hex number %x is visible.\n", 4242);
	len_new += ft_printf("ft_printf: \tthe hex number %x is visible.\n", 4242);
	printf("Printf = %d, ft_printf = %d\n\n", len_original, len_new);
}
*/
