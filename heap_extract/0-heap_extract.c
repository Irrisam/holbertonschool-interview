#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to the root of the heap
 * Return: the value stored in the root node, or 0.
 */
int heap_extract(heap_t **root)
{
	int value;
	heap_t *tmp, *node;

	if (!root || !*root)
		return (0);
	tmp = *root;
	value = tmp->n;
	if (!tmp->left && !tmp->right)
	{
		*root = NULL;
		free(tmp);
		return (value);
	}
	preorder_traversal(tmp, &node, check_height(tmp), 0);
	tmp = sort(tmp);
	tmp->n = node->n;
	if (node->parent->right)
		node->parent->right = NULL;
	else
		node->parent->left = NULL;
	free(node);
	return (value);
}
