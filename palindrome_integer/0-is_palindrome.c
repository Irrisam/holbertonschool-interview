#include "palindrome.h"

/**
 * is_palindrome - looks for palindrom
 * @n: the number
 *
 * Return: 1 if the number is a palindrome, 0 otherwise.
 */
int is_palindrome(unsigned long n)
{
	unsigned long original_n = n;
	unsigned long reversed_n = 0;

	while (n > 0)
	{
		reversed_n = reversed_n * 10 + (n % 10);
		n /= 10;
	}

	return (original_n == reversed_n);
}