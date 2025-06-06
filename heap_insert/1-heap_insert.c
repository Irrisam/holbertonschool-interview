#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_size - calculates the size of a binary tree
 * @tree: pointer to the root node of the tree
 *
 * Return: size of the tree, 0 if tree is NULL
 */
size_t heap_size(const heap_t *tree)
{
	if (tree == NULL)
		return (0);
	
	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * find_parent - finds the parent node where the new node should be inserted
 * @root: pointer to the root node
 * @index: index of the node to insert (1-based)
 * @size: current size of the heap
 *
 * Return: pointer to the parent node
 */
heap_t *find_parent(heap_t *root, size_t index, size_t size)
{
	char path[32];
	int i, path_len = 0;
	heap_t *current = root;
	size_t parent_index = index / 2;
	
	/* Convert parent index to binary path */
	while (parent_index > 1)
	{
		path[path_len++] = (parent_index % 2) ? 'R' : 'L';
		parent_index /= 2;
	}
	
	/* Follow the path from root to parent */
	for (i = path_len - 1; i >= 0; i--)
	{
		if (path[i] == 'L')
			current = current->left;
		else
			current = current->right;
	}
	
	return (current);
}

/**
 * swap_values - swaps values of two nodes
 * @node1: first node
 * @node2: second node
 */
void swap_values(heap_t *node1, heap_t *node2)
{
	int temp = node1->n;
	node1->n = node2->n;
	node2->n = temp;
}

/**
 * heapify_up - maintains max heap property by moving value up
 * @node: pointer to the inserted node
 */
void heapify_up(heap_t *node)
{
	while (node->parent && node->n > node->parent->n)
	{
		swap_values(node, node->parent);
		node = node->parent;
	}
}

/**
 * heap_insert - inserts a value into a Max Binary Heap
 * @root: double pointer to the root node of the Heap
 * @value: value to store in the node to be inserted
 *
 * Return: pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	size_t size, index;
	
	if (root == NULL)
		return (NULL);
	
	/* Create new node */
	new_node = malloc(sizeof(heap_t));
	if (new_node == NULL)
		return (NULL);
	
	new_node->n = value;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	
	/* If tree is empty, new node becomes root */
	if (*root == NULL)
	{
		*root = new_node;
		return (new_node);
	}
	
	/* Calculate size and find insertion point */
	size = heap_size(*root);
	index = size + 1; /* Next position to insert (1-based indexing) */
	
	/* Find parent node for insertion */
	parent = find_parent(*root, index, size);
	
	/* Insert as left or right child */
	new_node->parent = parent;
	if (parent->left == NULL)
		parent->left = new_node;
	else
		parent->right = new_node;
	
	/* Maintain max heap property */
	heapify_up(new_node);
	
	return (new_node);
}
