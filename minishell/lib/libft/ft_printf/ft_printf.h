/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:37:59 by goteixei          #+#    #+#             */
/*   Updated: 2024/12/13 00:26:09 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>

int			ft_printf(const char *format, ...);

// c
int			ft_print_char(int c);

// s
int			ft_print_str(char const *str);

// p
//static int			ft_ptr_len(unsigned long long n);
//static void	ft_put_ptr(unsigned long long n);
int			ft_print_ptr(unsigned long long *ptr);

//u
//int			ft_uns_len(unsigned int n);
//static void	ft_put_uns(int n);
int			ft_print_unsigned(unsigned int n);
//int	ft_print_unsigned(unsigned int nbr);

// i, d
//int			ft_nbr_len(int n);
//static void	ft_put_int(int n);
int			ft_print_int(int n);

// x, X
//int			ft_hex_len(unsigned int nbr);
//void		ft_put_hex(unsigned int nbr, const char format);
int			ft_print_hex(unsigned int nbr, const char format);

//%
int			ft_print_percent(void);

#endif