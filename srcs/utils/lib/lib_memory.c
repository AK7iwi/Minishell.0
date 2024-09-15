#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	tab = (char *)malloc(sizeof(*s) * (len + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*(unsigned char *)(s + i++) = (unsigned char)c;
	return (s);
}