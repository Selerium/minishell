/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:03:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/03 20:15:19 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// counts the characters in s[i] for malloc
static size_t	wordinstr_len(char const *s, char c, int qflag)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		qflag = get_quote_type(qflag, s[i]);
		if (s[i] == c && s[i] && qflag == 0)
			return (i);
		i++;
	}
	return (i);
}

char	**ms_split(char *s, char c)
{
	size_t		i;
	size_t		j;
	char		**str;
	int			qflag;

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
		qflag = get_quote_type(qflag, s[i]);
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
