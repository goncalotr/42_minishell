/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:17:43 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:01:04 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstiter
** 
** Prototype
** void ft_lstiter(t_list *lst, void (*f)(void *));
** 
** Turn in files
** -
** 
** Parameters
** lst: The address of a pointer to a node.
** f: The address of the function used to iterate on the list.
** 
** Return value
** None
** 
** External functs.
** None
** 
** Description
** Iterates the list ’lst’ and applies the function ’f’
** on the content of each node.
*/

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_content(void *content) {
    printf("Node content: %d\n", *(int *)content); // Print integer content
}

t_list *ft_lstnew(void *content) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (new_node == NULL) return NULL;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

int main() {
    t_list *head = NULL;

    for (int i = 1; i <= 3; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        t_list *new_node = ft_lstnew(value);
        new_node->next = head;
        head = new_node;
    }

    printf("Contents of the list:\n");
    ft_lstiter(head, print_content);

    t_list *current = head;
    while (current != NULL) {
        t_list *temp = current;
        current = current->next;
        free(temp->content);
        free(temp);
    }

    return 0;
}
*/
