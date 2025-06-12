/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:59:00 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 17:52:33 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_strmapi
** 
** Prototype
** char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
** 
** Turn in files
** -
** 
** Parameters
** s: The string on which to iterate.
** f: The function to apply to each character.
** 
** Return value
** The string created from the successive applications of ’f’.
** Returns NULL if the allocation fails.
** 
** External functs.
** malloc
** 
** Description
** Applies the function f to each character of the
** string s, passing its index as the first argument
** and the character itself as the second. A new
** string is created (using malloc(3)) to collect the
** results from the successive applications of f.
*/

/*
char to_upper_even(unsigned int index, char c) {
    if (index % 2 == 0 && c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[len] != '\0')
		len++;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	size_t test_number;
	char *result;
	char *str;

	test_number = 0;
	str = "HElllowdawdu";

	printf("Test %s\n", test_number);
	printf("Original %d: %s, %s\n", test_number, str, "to_upper_even");

	result = ft_strmapi(str, to_upper_even);
	printf("Result %d: %s\n", test_number, result);

	test_number++;
	printf("-----------------------\n");


	return (0);
}
*/