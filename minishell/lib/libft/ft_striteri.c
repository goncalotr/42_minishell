/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:57:34 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:20:11 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_striteri
** 
** Prototype
** void ft_striteri(char *s, void (*f)(unsigned int, char*));
** 
** Turn in files
** -
** 
** Parameters
** s: The string on which to iterate.
** f: The function to apply to each character.
** 
** Return value
** None
** 
** External functs.
** None
** 
** Description
** Applies the function ’f’ on each character of
** the string passed as argument, passing its index
** as first argument. Each character is passed by
** address to ’f’ to be modified if necessary.
*/

/*
void to_upper_even_in_place(unsigned int index, char *c) {
    if (index % 2 == 0 && *c >= 'a' && *c <= 'z')
        *c -= 32;
}
*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
	{
		return ;
	}
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	size_t test_number;
	char str[] = "HElllowdawdu";

	test_number = 0;

	printf("Test %zu\n", test_number);
	printf("Original %zu: %s, %s\n", test_number, str, "to_upper_even_in_place");

	ft_striteri(str, to_upper_even_in_place);
	printf("Result %zu: %s\n", test_number, str);

	test_number++;
	printf("-----------------------\n");

	char str2[] = "aaaaaaaaaaaaaaaaaaaaaaaaaa0000000
	00000000000ddddddddddddddddddddddddd";

	test_number = 0;

	printf("Test %zu\n", test_number);
	printf("Original %zu: %s, %s\n", test_number, str2
	 "to_upper_even_in_place");

	ft_striteri(str2, to_upper_even_in_place);
	printf("Result %zu: %s\n", test_number, str2);

	test_number++;
	printf("-----------------------\n");

	return (0);
}
*/
