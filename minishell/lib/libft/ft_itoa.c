/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:34:05 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 18:12:23 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_itoa
** 
** Prototype
** char *ft_itoa(int n);
** 
** Turn in files
** -
** 
** Parameters
** n: the integer to convert.
** 
** Return value
** The string representing the integer.
** NULL if the allocation fails.
** 
** External functs.
** malloc
** 
** Description
** Allocates (with malloc(3)) and returns a string
** representing the integer received as an argument.
** Negative numbers must be handled.
*/

#include "libft.h"

size_t	str_len(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

size_t	nbr_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*str_cpy(char *dest, char *src)
{
	char	*original_dest;

	original_dest = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}

char	*str_join(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = str_len(s1);
	s2_len = str_len(s2);
	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	str_cpy(result, s1);
	str_cpy(result + s1_len, s2);
	return (result);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*result;
	long	number;

	number = n;
	len = nbr_len(number);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (number < 0)
	{
		result[0] = '-';
		number *= -1;
	}
	if (number == 0)
		result[0] = '0';
	while (number > 0)
	{
		result[--len] = (number % 10) + '0';
		number /= 10;
	}
	return (result);
}

/*
#include <stdio.h>

int main(void)
{
	int test_nbrs[] = {5, 124, -4, -420, 0, -2147483648};
	int test_count = sizeof(test_nbrs) / sizeof(test_nbrs[0]);
	int test_i = 0;
	while (test_i < test_count)
	{
		char *result = ft_itoa(test_nbrs[test_i]);
		printf("Test %d: %d\nResult: %s\n\n", test_i, test_nbrs[test_i], result);
		//free(result);
		test_i++;
	}
	return (0);
}
*/
