#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > (unsigned int)ft_strlen(s) - start)
		len = (unsigned int)ft_strlen(s) - start;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len && s[(size_t)start + i])
	{
		res[i] = s[(size_t)start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j] = s2[i];
		j++;
		i++;
	}
	str[j] = '\0';
	return (str);
}

const char	*cpy(char const *str, char *word, char c)
{
	int	i;

	i = 0;
	while (*str && !((*str == c)))
	{
		word[i] = *str;
		str++;
		i++;
	}
	word[i] = '\0';
	return (str);
}

void	*ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

int	word_len(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] && (str[i] == c))
		i++;
	while (str[i] && !((str[i] == c)))
	{
		len++;
		i++;
	}
	return (len);
}

int	c_words(char const *str, char set)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (!((str[i] == set)) && (((str[i + 1] == set)) || str[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w_len;
	char	**strs;

	if (!s)
		return (NULL);
	strs = (char **)malloc((c_words(s, c) + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			w_len = word_len(s, c);
			strs[i] = (char *)malloc((w_len + 1) * sizeof(char));
			if (!strs[i])
				return (ft_free(strs, i));
			s = cpy(s, strs[i++], c);
		}
	}
	strs[i] = 0;
	return (strs);
}