/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:03:15 by jpedro-f          #+#    #+#             */
/*   Updated: 2024/11/15 17:03:17 by jpedro-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MAX_FD 1024

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list_gnl
{
	char				*str;
	struct s_list_gnl	*next;
}	t_list_gnl;

void		ft_list_prep(t_list_gnl **list);
char		*ft_get_line(t_list_gnl *list);
void		ft_append_list(t_list_gnl **list, char *buf);
void		ft_list_add(t_list_gnl **list, int fd);
char		*get_next_line(int fd);
void		ft_dealloc(t_list_gnl **list, t_list_gnl *clean_node, char *buf);
int			ft_len_list(t_list_gnl *list);
void		ft_copy_str(t_list_gnl *list, char *new_str);
t_list_gnl	*ft_find_last_node(t_list_gnl *list);
int			ft_found_newline(t_list_gnl *list);

#endif
