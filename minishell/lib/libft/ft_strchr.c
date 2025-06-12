/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:52:21 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/11 01:22:14 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        strchr, strrchr, strchrnul - locate character in string
** 
** SYNOPSIS
**        #include <string.h>
** 
**        char *strchr(const char *s, int c);
** 
**        char *strrchr(const char *s, int c);
** 
**        #define _GNU_SOURCE         See feature_test_macros(7)
**        #include <string.h>
** 
**        char *strchrnul(const char *s, int c);
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	cc = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == cc)
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

/*
#include <stdio.h>

int main()
{
    const char *test_strings[] = {
        "Hello, World!",
        "abc",
        "",
        "1234567890"
    };

    char test_chars[] = {'W', 'o', 'z', '\0', 'a', 'c', '1', '\0'};
    int num_tests = sizeof(test_chars) / sizeof(test_chars[0]);

    for (int i = 0; i < num_tests; i++)
    {
        const char *str = test_strings[i / 3];
        char c = test_chars[i];

        char *result = ft_strchr(str, c);
        char *expected = strchr(str, c);

        printf("Testing ft_strchr(\"%s\", '%c'):\n", str, c);
        if (result == expected)
        {
            printf("    Passed: Found at %s\n", result ? result : "NULL");
        }
        else
        {
            printf("    Failed: Expected %s but got %s\n", expected ?
			expected : "NULL", result ? result : "NULL");
        }
        printf("\n");
    }

	return (0);
}
*/
