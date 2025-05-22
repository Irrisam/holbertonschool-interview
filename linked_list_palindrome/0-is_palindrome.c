#include <stdlib.h>
#include <stdio.h>
#include "lists.h"

/**
 * is_palindrome - checks if a linked list is a palindrome
 * @head: pointer to pointer to head of list
 * Return: 1 if palindrome, 0 if not
 */
int is_palindrome(listint_t **head)
{
    listint_t *slow = *head;
    listint_t *fast = *head;
    listint_t *stack = NULL;
    listint_t *new_node, *temp;

    if (*head == NULL || (*head)->next == NULL)
        return (1);

    /* Find middle and build stack of first half */
    while (fast != NULL && fast->next != NULL)
    {
        /* Push slow->n onto stack */
        new_node = malloc(sizeof(listint_t));
        if (new_node == NULL)
            return (0);
        new_node->n = slow->n;
        new_node->next = stack;
        stack = new_node;

        slow = slow->next;
        fast = fast->next->next;
    }

    /* Skip middle element if odd length */
    if (fast != NULL)
        slow = slow->next;

    /* Compare second half with stack */
    while (slow != NULL)
    {
        if (stack == NULL || stack->n != slow->n)
        {
            /* Free remaining stack */
            while (stack != NULL)
            {
                temp = stack;
                stack = stack->next;
                free(temp);
            }
            return (0);
        }
        
        /* Pop from stack */
        temp = stack;
        stack = stack->next;
        free(temp);
        
        slow = slow->next;
    }

    /* Free any remaining stack */
    while (stack != NULL)
    {
        temp = stack;
        stack = stack->next;
        free(temp);
    }

    return (1);
}
