/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:48 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/27 16:27:57 by jebucoy          ###   ########.fr       */
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

char	*eliminate_quotes(char *input, size_t *idx, int qflag)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*final;
	size_t	end_len;

	end_len = 0;
	if (qflag != 0 && (*idx) == 0)
	{
		tmp1 = ft_substr(input, *idx + 1, )
	}
}

char	*trim_quotes(char *input, int qflag)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		qflag = is_quotes_closed(qflag, input[i]);
		if (qflag != 0)
			input = eliminate_quotes(input, &i, qflag);
		i++;
	}
}
