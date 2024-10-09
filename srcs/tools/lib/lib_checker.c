#include "minishell.h"

bool find_equal(char *var)
{
	size_t i;

	i = 0;

	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	
	return (false);
}
inline bool	ft_isalnum(int c)
{   
	return (ft_isalpha(c) || (c >= '0' && c <= '9'));
}

inline bool	ft_isalpha(int c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}