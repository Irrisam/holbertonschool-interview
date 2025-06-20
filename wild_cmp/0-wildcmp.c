#include "holberton.h"

/**
 * wildcmp - Evaluates if two strings are equivalent, supporting wildcards
 * @s1: Input string one
 * @s2: Input string two, which may include '*' as a wildcard
 *
 * Return: 1 if both strings can be treated as matching, else 0
 */
int wildcmp(char *s1, char *s2)
{
	if (*s2 == '\0')
		return (*s1 == '\0');

	if (*s2 == '*')
	{
		if (wildcmp(s1, s2 + 1))
			return (1);

		if (*s1 != '\0' && wildcmp(s1 + 1, s2))
			return (1);

		return (0);
	}

	if (*s1 == '\0' || *s1 != *s2)
		return (0);

	return (wildcmp(s1 + 1, s2 + 1));
}
