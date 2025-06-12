/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:44:34 by goteixei          #+#    #+#             */
/*   Updated: 2024/12/13 14:38:58 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_formats(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		len += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
		len += ft_print_ptr(va_arg(args, unsigned long long *));
	else if (format == 'u')
		len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'd' || format == 'i')
		len += ft_print_int(va_arg(args, int));
	else if (format == 'x' || format == 'X')
		len += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		len += ft_print_percent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		len;
	va_list	args;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			len += ft_print_char(str[i]);
		}
		else
		{
			len += ft_formats(args, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

/*
#include <stdio.h>

int main(void)
{
    int custom_ret, original_ret;
    int test_number = 0;

    //NO SPECIFIERS TESTS 
    printf("========== NO SPECIFIERS TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("Hello World\n");
    original_ret = printf("Hello World\n");
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //PERCENT SIGN TESTS
    printf("========== PERCENT SIGN TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%%\n");
    original_ret = printf("%%\n");
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //CHAR TESTS
    printf("========== CHAR TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%c\n", 'A');
    original_ret = printf("%c\n", 'A');
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //STRING TESTS
    printf("========== STRING TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%s\n", "Test String");
    original_ret = printf("%s\n", "Test String");
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //INTEGER TESTS
    printf("========== INTEGER TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%d\n", 12345);
    original_ret = printf("%d\n", 12345);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //UNSIGNED TESTS
    printf("========== UNSIGNED TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%u\n", 4294967295U);
    original_ret = printf("%u\n", 4294967295U);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //HEXADECIMAL (LOWERCASE) TESTS
    printf("========== HEXADECIMAL x TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%x\n", 255);
    original_ret = printf("%x\n", 255);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //HEXADECIMAL (UPPERCASE) TESTS
    printf("========== HEXADECIMAL X TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%X\n", 255);
    original_ret = printf("%X\n", 255);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //POINTER TESTS
    printf("========== POINTER TESTS ==========");
    test_number++;
    int num = 42;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%p\n", &num);
    original_ret = printf("%p\n", &num);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //MIXED TESTS
    printf("========== MIXED TESTS ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("Char: %c, String: %s, Int: %d, Unsigned: %u, \
Hex: %x\n", 'B', "Mix", -123, 123U, 0xABC);
    original_ret = printf("Char: %c, String: %s, Int: %d, Unsigned: %u, \
Hex: %x\n", 'B', "Mix", -123, 123U, 0xABC);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //EDGE CASE TESTS

    //Large Integer
    printf("========== LARGE INTEGER ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%d\n", 2147483647);
    original_ret = printf("%d\n", 2147483647);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //Long String
    printf("========== LONG STRING ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%s\n", "This is a very long string designed \
to test the printf function's handling of substantial input without failing.");
    original_ret = printf("%s\n", "This is a very long string designed \
to test the printf function's handling of substantial input without failing.");
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    //Complex String Formatting
    printf("========== COMPLEX STRING FORMATTING ==========");
    test_number++;
    printf("\nTest %d:\n", test_number);
    custom_ret = ft_printf("%% Complete: %d%%\n", 75);
    original_ret = printf("%% Complete: %d%%\n", 75);
    printf("Custom: %d | Original: %d\n", custom_ret, original_ret);
    printf("------------------------------------------\n");

    return 0;
}
*/
