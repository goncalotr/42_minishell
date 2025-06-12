/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:18:44 by goteixei          #+#    #+#             */
/*   Updated: 2025/02/09 12:08:21 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
//#  define BUFFER_SIZE 42
//#  define BUFFER_SIZE 1
//#  define BUFFER_SIZE 10
#  define BUFFER_SIZE 1000000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024  // A reasonable default value
# endif

// *malloc() free() read()
# include <stdlib.h>
# include <unistd.h>
//for OPEN_MAX
# include <limits.h>

char	*get_next_line(int fd);

//char	*ft_free(char *str1, char *str2);
//char	*ft_next(char *buffer);
//char	*ft_line(char *buffer);
//char	*read_file(int fd, char *res);

/*
void	*ft_bzero(void *s, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
*/

#endif