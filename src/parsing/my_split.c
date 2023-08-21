#include"../../include/minishell.h"

static int	str_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if ((s[i] == c && s[i]) || (s[i + 1] == 0))
		{
			count++;
			while (s[i] == c && s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (count);
}

// counts the characters in s[i] for malloc

static int	wordinstr_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i])
			return (i);
		i++;
	}
	return (i);
}

char	**my_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, wordinstr_len(&s[i], c));
			i += wordinstr_len(&s[i], c);
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}