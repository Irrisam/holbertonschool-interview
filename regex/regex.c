#include "regex.h"

/**
 * regex_match - Determines if a string fits a given regex pattern
 * @str: Input string to validate
 * @pattern: Regex pattern to evaluate against
 *
 * Return: 1 if there is a valid match, otherwise 0
 */
int regex_match(char const *str, char const *pattern)
{
	if (!*pattern)
		return (!*str);

	if (*(pattern + 1) == '*')
	{
		if (regex_match(str, pattern + 2))
			return (1);

		if (*str && (*str == *pattern || *pattern == '.'))
			return (regex_match(str + 1, pattern));

		/* No match in either scenario */
		return (0);
	}

	if (*str && (*str == *pattern || *pattern == '.'))
		return (regex_match(str + 1, pattern + 1));

	return (0);
}
