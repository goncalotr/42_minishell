/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goteixei <goteixei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:57:44 by goteixei          #+#    #+#             */
/*   Updated: 2024/11/04 00:51:33 by goteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Function name
** ft_lstlast
** 
** Prototype
** t_list *ft_lstlast(t_list *lst);
** 
** Turn in files
** -
** 
** Parameters lst:
** The beginning of the list.
** 
** Return value
** Last node of the list
** 
** External functs.
** None
** 
** Description
** Returns the last node of the list.
*/

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

/*
#include <stdio.h>

int ft_lstsize(t_list *lst)
{
	int count;

	count = 0;

	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return count;
}

t_list *ft_lstnew(void *content)
{
	t_list *new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}

void ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return;
	new->next = *lst;
	*lst = new;
}

void print_list(t_list *lst) {
    t_list *current = lst;
    while (current != NULL) {
        printf("- Node content: %d\n", *(int *)current->content);
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
    ft_lstadd_front(&head, node3);

    int size = ft_lstsize(head);
    printf("The size of the list is: %d\n", size);

    printf("Contents of the list:\n");
    print_list(head);

    t_list *last_node = ft_lstlast(head);
    if (last_node != NULL) {
        printf("The last node content is: %d\n", *(int *)last_node->content);
    } else {
        printf("The list is empty.\n");
    }

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
