/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:14:30 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/10 23:55:11 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        toupper, tolower, toupper_l, tolower_l - convert uppercase or lowercase
** 
** SYNOPSIS
**        #include <ctype.h>
** 
**        int toupper(int c);
**        int tolower(int c);
** 
**        int toupper_l(int c, locale_t locale);
**        int tolower_l(int c, locale_t locale);
** 
**    Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
** 
**        toupper_l(), tolower_l():
**            Since glibc 2.10:
**                   _XOPEN_SOURCE >= 700
**            Before glibc 2.10:
**                   _GNU_SOURCE
*/

#include "libft.h"

int	ft_toupper(int c)
{
	int	nb;
	int	nc;

	if (c >= 'a' && c <= 'z')
	{
		nb = c - 'a';
		nc = 'A' + nb;
		return (nc);
	}
	else
	{
		return (c);
	}
	return (0);
}

/*
#include <stdio.h>

int main()
{
	char str1 = 'z';
	printf("Original: %c\n", str1);
	// Function usage
	int result1 = ft_toupper(str1);
	printf("Result: %c\n", result1);

	char str2 = 'F';
	printf("Original: %c\n", str2);
	// Function usage
	int result2 = ft_toupper(str2);
	printf("Result: %c\n", result2);

	char str3 = '9';
	printf("Original: %c\n", str3);
	// Function usage
	int result3 = ft_toupper(str3);
	printf("Result: %c\n", result3);

	char str4 = ' ';
	printf("Original: %c\n", str4);
	// Function usage
	int result4 = ft_toupper(str4);
	printf("Result: %c\n", result4);
	return (0);
}
*/
