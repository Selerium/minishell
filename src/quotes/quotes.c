/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:48 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/28 19:12:52 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// qflag = 0
// if single quote (\') is encounted, set it to one
// if double quote (\") set it to 2
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

char	*eliminate_quotes(char *input, size_t *idx, int qflag, size_t start)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*final;

	printf("start: %zd\n", start);
	printf("eliminiate_quotes() input: [%s]\n", input);
	if (start == 0)
		tmp1 = ft_strdup("");
	else
		tmp1 = ft_substr(input, 0, (*idx) - 1);
	printf("tmp1: [%s]\n", tmp1);
	start = *idx;
	while (input[*idx] && qflag != 0)
		(*idx)++;
	tmp2 = ft_substr(input, start + 1, (*idx) - 2);
	printf("tmp2: [%s]\n", tmp2);
	tmp3 = ft_substr(input, (*idx + 1), ft_strlen(input) - (*idx));
	printf("index value: %zd\n", *idx);
	printf("tmp3: [%s]\n", tmp3);
	final = ft_strjoin(tmp1, tmp2);
	free (input);
	input = ft_strjoin(final, tmp3);
	free(tmp1);
	free(tmp2);
	free(tmp3);
	free(final);
	return (input);
}

char	*trim_quotes(char *input)
{
	size_t	i;
	size_t	start;
	int		qflag;

	i = 0;
	start = 0;
	qflag = 0;
	while (input[i])
	{
		printf("trim_quotes input: [%s]\n", input);
		qflag = is_quotes_closed(qflag, input[i]);
		if (qflag != 0)
		{
			start = i;
			// while (input[i] && qflag != 0)
			// 	i++;
			input = eliminate_quotes(input, &i, qflag, start);
		}
		i++;
	}
	return (input);
}
