/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:48:30 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 22:11:16 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        memmove - copy memory area
** 
** SYNOPSIS
**        #include <string.h>
** 
**        void *memmove(void *dest, const void *src, size_t n);
** 
** DESCRIPTION
**        The memmove() function copies n bytes from memory
**         area src to memory area dest.
**        The memory areas may overlap: copying takes place
**        as though the  bytes  in  src are  first copied into
**        a temporary array that does not overlap src or dest, and
**        the bytes are then copied from the temporary array to dest.
** 
** RETURN VALUE
**        The memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (n-- > 0)
		{
			d[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

/*
#include <stddef.h>
#include <stdio.h>

int main()
{
	char str1[] = "Test1234567890text for ft_memmove function";
	char str2[100];
	printf("\nSource: %s\n", str1);

	// Function usage
	ft_memmove(str2, str1, sizeof(str1));

	printf("\nDestination using ft_memmove(): %s\n", str2);
	return (0);
}
*/