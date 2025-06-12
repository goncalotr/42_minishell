/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:22:18 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/08 22:06:05 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        strdup, strndup, strdupa, strndupa - duplicate a string
** 
** SYNOPSIS
**        #include <string.h>
** 
**        char *strdup(const char *s);
** 
**        char *strndup(const char *s, size_t n);
**        char *strdupa(const char *s);
**        char *strndupa(const char *s, size_t n);
** 
**  Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
** 
**        strdup():
**            _XOPEN_SOURCE >= 500
**                || Since glibc 2.12: _POSIX_C_SOURCE >= 200809L
**                || Glibc versions <= 2.19: _BSD_SOURCE || _SVID_SOURCE
**        strndup():
**            Since glibc 2.10:
**                _POSIX_C_SOURCE >= 200809L
**            Before glibc 2.10:
**                _GNU_SOURCE
**        strdupa(), strndupa(): _GNU_SOURCE
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *) malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main()
{
    const char *str1 = "Hello, World!";
    char *dup1 = ft_strdup(str1);
    printf("Test 1: %s\n", (dup1 != NULL &&
	 strcmp(str1, dup1) == 0) ? "Passed" : "Failed");
    free(dup1);

    const char *str2 = "";
    char *dup2 = ft_strdup(str2);
    printf("Test 2: %s\n", (dup2 != NULL &&
strcmp(str2, dup2) == 0) ? "Passed" : "Failed");
    free(dup2);

    const char *str3 = "Line1\nLine2\tTabbed";
    char *dup3 = ft_strdup(str3);
    printf("Test 3: %s\n", (dup3 != NULL && 
	strcmp(str3, dup3) == 0) ? "Passed" : "Failed");
    free(dup3);

    const char *str4 = NULL;
    if (ft_strdup(str4) == NULL) 
        printf("Test 4: Passed\n");
    else
        printf("Test 4: Failed");

	return (0);
}
*/
