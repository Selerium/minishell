#include"../../include/minishell.h"

static size_t	str_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

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

// qflag = 0
// if single quote (') is encounted, set it to one
// if double quote (") set it to 2
// if a closing quote of the specific is encountered, reset to 0
int	is_quotes_closed(int qflag, char q)
{
	if (q == SINGLE && qflag == 0)
		return (1);
	else if (q == DOUBLE && qflag == 0)
		return (2);
	else if (q == SINGLE && qflag == 1)
		return (0);
	else if (q == DOUBLE && qflag == 2)
		return (0);
	return (qflag);

}

// counts the characters in s[i] for malloc
static size_t	wordinstr_len(char const *s, char c, int qflag)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		qflag = is_quotes_closed(qflag, s[i]);
		if (s[i] == c && s[i] && qflag == 0)
			return (i);
		i++;
	}
	return (i);
}


char	**my_split(char *s, char c)
{
	size_t		i;
	size_t		j;
	char	**str;
	int		qflag;

	i = 0;
	j = 0;
	qflag = 0;
	if (s == NULL)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		qflag = is_quotes_closed(qflag, s[i]);
		if (s[i] != c && qflag == 0)
		{
			str[j] = ft_substr(s, i, wordinstr_len(&s[i], c, qflag));
			i += wordinstr_len(&s[i], c, qflag);
			j++;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (str);
}