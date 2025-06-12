/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:00:11 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/10 22:31:57 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** NAME
**        malloc, free, calloc, realloc, reallocarray -
**        allocate and free dynamic memory
** 
** SYNOPSIS
**        #include <stdlib.h>
** 
**        void *malloc(size_t size);
**        void free(void *ptr);
**        void *calloc(size_t nmemb, size_t size);
**        void *realloc(void *ptr, size_t size);
**        void *reallocarray(void *ptr, size_t nmemb, size_t size);
** 
**    Feature Test Macro Requirements for glibc
**    (see feature_test_macros(7)):
** 
**        reallocarray():
**            Since glibc 2.29:
**                _DEFAULT_SOURCE
**            Glibc 2.28 and earlier:
**                _GNU_SOURCE
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main()
{
    int *arr1 = (int *)ft_calloc(5, sizeof(int));
    if (arr1 != NULL && arr1[0] == 0 && arr1[4] == 0)
        printf("Test 1 Passed: Memory is initialized to zero\n");
    else
        printf("Test 1 Failed\n");
    free(arr1);

    char *arr2 = (char *)ft_calloc(5, sizeof(char));
    if (arr2 != NULL && arr2[0] == '\0' && arr2[4] == '\0')
        printf("Test 2 Passed: Memory is initialized to zero\n");
    else
        printf("Test 2 Failed\n");
    free(arr2);

    char *arr3 = (char *)ft_calloc(0, sizeof(char));
    if (arr3 != NULL)
        printf("Test 3 Passed: Allocation with zero size\n");
    else
        printf("Test 3 Failed\n");
    free(arr3);

    int *arr4 = (int *)ft_calloc(1000, sizeof(int));
    int is_zeroed = 1;
    for (size_t i = 0; i < 1000; i++)
    {
        if (arr4[i] != 0)
        {
            is_zeroed = 0;
            break;
        }
    }
    if (is_zeroed)
        printf("Test 4 Passed: Large memory block initialized to zero\n");
    else
        printf("Test 4 Failed\n");
    free(arr4);

    void *arr5 = ft_calloc(SIZE_MAX, SIZE_MAX);
    if (arr5 == NULL)
        printf("Test 5 Passed: Correctly handled allocation failure\n");
    else
    {
        printf("Test 5 Failed\n");
        free(arr5);
    }

    return 0;
}
*/
