#include "binary_trees.h"

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to the root node of the heap
 * Return: value stored in the root node, or 0 if function fails
 */
int heap_extract(heap_t **root)
{
    heap_t *current, *last_node, *parent;
    int root_value, temp;
    size_t heap_size = 0, path, size_copy;
    heap_t *queue[1024];
    int front = 0, rear = 0;
    
    if (!root || !*root)
        return (0);
    
    root_value = (*root)->n;
    
    /* Calculate heap size using level-order traversal */
    queue[rear++] = *root;
    while (front < rear)
    {
        current = queue[front++];
        heap_size++;
        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }
    
    /* If only one node, just free it and return */
    if (heap_size == 1)
    {
        free(*root);
        *root = NULL;
        return (root_value);
    }
    
    /* Find the last node using binary path calculation */
    current = *root;
    path = heap_size;
    while (path > 1)
        path /= 2;
    
    size_copy = heap_size - path;
    while (path > 1)
    {
        path /= 2;
        if (size_copy >= path)
        {
            current = current->right;
            size_copy -= path;
        }
        else
            current = current->left;
    }
    last_node = current;
    parent = last_node->parent;
    
    /* Replace root value with last node value */
    (*root)->n = last_node->n;
    
    /* Remove the last node */
    if (parent)
    {
        if (parent->right == last_node)
            parent->right = NULL;
        else
            parent->left = NULL;
    }
    free(last_node);
    
    /* Heapify down - restore max heap property */
    current = *root;
    while (current)
    {
        heap_t *largest = current;
        
        /* Find the largest among current, left child, and right child */
        if (current->left && current->left->n > largest->n)
            largest = current->left;
        
        if (current->right && current->right->n > largest->n)
            largest = current->right;
        
        /* If largest is current node, heap property is satisfied */
        if (largest == current)
            break;
        
        /* Swap values and continue with the child that was swapped */
        temp = current->n;
        current->n = largest->n;
        largest->n = temp;
        current = largest;
    }
    
    return (root_value);
}