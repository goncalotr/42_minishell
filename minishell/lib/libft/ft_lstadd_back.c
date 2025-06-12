/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:10:14 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 01:01:45 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstadd_back
** 
** Prototype
** void ft_lstadd_back(t_list **lst, t_list *new);
** 
** Turn in files
** -
** 
** Parameters
** lst: The address of a pointer to the first link of a list.
** new: The address of a pointer to the node to be added to the list.
** 
** Return value
** None
** 
** External functs.
** None
** 
** Description
** Adds the node ’new’ at the end of the list.
*/

#include "libft.h"

/**
 * ft_lstadd_back - Adds a new node at the end of the linked list.
 * @lst: The address of a pointer to the first link of a list.
 * @new: The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last_node = *lst;
		while (last_node->next != NULL)
		{
			last_node = last_node->next;
		}
		last_node->next = new;
	}
}

/*
#include <stdio.h>
#include <stdlib.h>

t_list *ft_lstnew(void *content) {
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (new_node == NULL) return NULL;
    new_node->content = content;
    new_node->next = NULL;
    return new_node;
}

void ft_lstadd_front(t_list **lst, t_list *new) {
    new->next = *lst;
    *lst = new;
}

void print_list(t_list *lst) {
    t_list *current = lst;
    while (current != NULL) {
        printf("Node content: %d\n", *(int *)current->content);
        current = current->next;
    }
}

int main() {
    t_list *head = NULL;

    int *value1 = malloc(sizeof(int)); *value1 = 42;
    t_list *node1 = ft_lstnew(value1);
    ft_lstadd_front(&head, node1);

    int *value2 = malloc(sizeof(int)); *value2 = 100;
    t_list *node2 = ft_lstnew(value2);
    ft_lstadd_front(&head, node2);

    int *value3 = malloc(sizeof(int)); *value3 = 200;
    t_list *node3 = ft_lstnew(value3);
    ft_lstadd_back(&head, node3);

    printf("Contents of the list:\n");
    print_list(head);

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
