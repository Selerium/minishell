/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:48 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/23 16:25:35 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*remove_quotes(char *input)
{
	size_t	i;
	size_t	j;
	char	*unquoted;
	int		qflag;
	int		nquote;

	i = 0;
	j = 0;
	nquote = 0;
	unquoted = NULL;
	while (input && input[i])
	{
		qflag = is_quotes_closed(qflag, input[i]);
		if ((qflag != 0) && (input[i] == SINGLE || input[i] == DOUBLE))
			nquote++;
		
	}
	if (input[i] == '\0' && nquote == 0)
		return (input);
	unquoted[j] = '\0';
	return (unquoted);
}

void	unquote(char **input)
{
	size_t	i;

	i = 0;
	while (input && input[i])
	{
		input[i] = remove_quotes(input[i]);
		i++;
	}
}
