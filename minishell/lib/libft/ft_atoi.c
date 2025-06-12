/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:46:18 by goteixei          #+#    #+#             */
/*   Updated: 2025/02/01 10:19:38 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        atoi, atol, atoll - convert a string to an integer
** 
** SYNOPSIS
**        #include <stdlib.h>
** 
**        int atoi(const char *nptr);
**        long atol(const char *nptr);
**        long long atoll(const char *nptr);
** 
**    Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
** 
**        atoll():
**            _ISOC99_SOURCE ||
**                ||  Glibc versions <= 2.19:  _BSD_SOURCE || _SVID_SOURCE
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

/*
#include <stdio.h>


int main(void)
{
    const char *test_cases[] = {
        "42",
        "-42",
        "   +42",
        "   ---42",
        "4193 with words",
        "words and 987",
        "2147483647", // INT_MAX
        "-2147483648", // INT_MIN
        "2147483648", // Overflow
        "-2147483649", // Underflow
        "   +0",
		"----++++  -42", //+ and spaces
		"\t\v\f\r\n \f+\t\v\f\r\n \f1234",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("\nTest %d\nInput: '%s'\nOriginal Output:%d\nlibftOutput: %d\n", 
		i, test_cases[i], atoi(test_cases[i]), ft_atoi(test_cases[i]));
    }

    printf("%d, %d",ft_atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234"),
	atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234"));

	int i1 = ft_atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234");
	int i2 = atoi("\t\v\f\r\n \f+\t\v\f\r\n \f1234");
	if (i1 == i2)
	{
		printf("\n1\n");
		return (1);
	}
    return 0;
}
*/
