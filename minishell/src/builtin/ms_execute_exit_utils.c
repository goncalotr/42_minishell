/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_exit_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-fvm <jpedro-fvm@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:23:19 by goteixei          #+#    #+#             */
/*   Updated: 2025/06/30 15:25:05 by jpedro-fvm       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
c == '\v' || c == '\f' || c == '\r');
}

/**
 * @brief Helper for atol_validate to check for overflow before calculation.
 *
 * positive workflow
 * negative workflow
 */
static bool	ft_check_overflow(long long result, int digit, int sign)
{
	if (sign == 1)
	{
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX \
/ 10 && digit > LLONG_MAX % 10))
			return (true);
	}
	else if (sign == -1)
	{
		if (result > -(LLONG_MIN / 10) || (result == -(LLONG_MIN / 10) \
&& digit > -(LLONG_MIN % 10)))
			return (true);
	}
	return (false);
}

/*
** @brief Skips whitespace and parses the optional sign (+ or -).
** @param str The input string.
** @param i_ptr Pointer to the current index in the string (will be updated).
** @return Returns 1 for positive sign (or no sign) and -1 for negative sign.
*/
static int	ft_atol_val_parse_sign_and_whitespace(const char *str, int *i_ptr)
{
	int	sign;

	sign = 1;
	while (ft_isspace(str[*i_ptr]))
		(*i_ptr)++;
	if (str[*i_ptr] == '-' || str[*i_ptr] == '+')
	{
		if (str[*i_ptr] == '-')
			sign = -1;
		(*i_ptr)++;
	}
	return (sign);
}

/**
 * @brief Attempts to convert a string to a long long, checking for validity.
 *        Checks for overflow and ensures the entire string represents a number
 *        (allowing optional leading '+' or '-').
 * @param str The string to convert.
 * @param n_out Pointer where the resulting long long will be stored if valid.
 * @return true if the string is a valid representation of a long long,
 *         false otherwise (overflow, non-digit characters).
 * 
 * ft_isdigit -> must have at least one digit
 * second ft_isspace -> check for trailing spaces
 * before multiplying or adding we check that the result * 10 won't overflow
 */
bool	ft_atol_validate(const char *str, long long *n_out)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	i = 0;
	sign = ft_atol_val_parse_sign_and_whitespace(str, &i);
	if (!ft_isdigit(str[i]))
		return (false);
	while (ft_isdigit(str[i]))
	{
		if (ft_check_overflow(result, str[i] - '0', sign))
			return (false);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	*n_out = sign * result;
	return (str[i] == '\0');
}
