#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_size - measures the size
 */
size_t heap_size(const heap_t *tree)
{
	if (!tree)
		return (0);
	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * get_last_node - last level-order
 */
heap_t *get_last_node(heap_t *root, size_t size)
{
	heap_t *node = root;
	size_t mask;
	int bit;

	if (size == 1)
		return (root);

	for (mask = 1; mask <= size; mask <<= 1)
		;
	mask >>= 2;

	while (mask > 0)
	{
		bit = (size & mask) ? 1 : 0;
		if (bit)
			node = node->right;
		else
			node = node->left;
		mask >>= 1;
	}
	return (node);
}

/**
 * heapify_down - moving node down
 */
void heapify_down(heap_t *node)
{
	heap_t *largest = node;
	int temp;

	if (!node)
		return;

	if (node->left && node->left->n > largest->n)
		largest = node->left;

	if (node->right && node->right->n > largest->n)
		largest = node->right;

	if (largest != node)
	{
		temp = node->n;
		node->n = largest->n;
		largest->n = temp;
		heapify_down(largest);
	}
}

/**
 * heap_extract - extracts the root node
 */
int heap_extract(heap_t **root)
{
	heap_t *last_node, *parent;
	int root_value;
	size_t size;

	if (!root || !*root)
		return (0);

	root_value = (*root)->n;
	size = heap_size(*root);

	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (root_value);
	}

	last_node = get_last_node(*root, size);
	parent = last_node->parent;

	(*root)->n = last_node->n;

	if (parent->right == last_node)
		parent->right = NULL;
	else
		parent->left = NULL;

	free(last_node);

	heapify_down(*root);

	return (root_value);
}
