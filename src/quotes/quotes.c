/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:54:48 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/03 13:23:46 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* qflag = 0
if single quote (\') is encounted, set it to one
if double quote (\") set it to 2
if a closing quote of the specific is encountered, reset to 0*/
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

// char	*eliminate_quotes(char *input, size_t *idx, int qflag)
// {
// 	char	*tmp1;
// 	char	*tmp2;
// 	char	*tmp3;
// 	char	*final;

// 	printf("1 input[%zd] : [%c] | qflag value: %d\n", *idx, input[*idx], qflag);
// 	tmp1 = ft_substr(input, 0, (*idx));
// 	// start = *idx;
// 	// (*idx)++;
// 	// while (input[*idx] && qflag != 0)
// 	// {
// 	// 	qflag = is_quotes_closed(qflag, input[*idx]);
// 	// 	printf("qflag = %d\n", qflag);
// 	// 	if (qflag == 0)
// 	// 		break ;
// 	// 	(*idx)++;
// 	// }
// 	tmp2 = ft_substr(input, start + 1, (*idx) - (start + 1));
// 	printf("tmp2: [%s]\n", tmp2);
// 	tmp3 = ft_substr(input, (*idx + 1), ft_strlen(input) - (*idx));
// 	printf("tmp3: [%s]\n", tmp3);
// 	final = ft_strjoin(tmp1, tmp2);
// 	free (input);
// 	input = ft_strjoin(final, tmp3);
// 	free(tmp1);
// 	free(tmp2);
// 	free(tmp3);
// 	free(final);
// 	// (*idx)--;
// 	return (input);
// }

char	*eliminate_quotes(char *input, size_t *idx, int qflag, int old_qflag) 
{
	char	*tmp1;
	char	*tmp2;
	size_t	start;

	(void)old_qflag;
	tmp1 = ft_substr(input, 0, (*idx));
	printf("tmp1: [%s]\n", tmp1);
	start = (*idx) + 1;
	while (qflag != 0)
	{
		qflag = is_quotes_closed(qflag, input[*idx]);
		printf("input[%zd] = [%c] | qflag = %d\n", *idx, input[*idx], qflag);
		(*idx)++;
	}
	tmp2 = ft_substr(input, start, ft_strlen(input) - start -1);
	printf("tmp2: [%s]\n", tmp2);
	// tmp2 = ft_substr(input, *idx + 1, ft_strlen(input) - (*idx) - 1);
	free (input);
	input = ft_strjoin(tmp1, tmp2);
	(*idx)--;
	free (tmp1);
	free (tmp2);
	return (input);
}

char	*trim_quotes(char *input)
{
	size_t	i;
	int		qflag;
	int		old_qflag;

	i = 0;
	qflag = 0;
	while (input[i])
	{
		old_qflag = qflag;
		qflag = is_quotes_closed(qflag, input[i]);
		if ((qflag != 0) || (!qflag && old_qflag))
		{
			printf("qflag = %d | old_qflag = %d\n", qflag, old_qflag);
			input = eliminate_quotes(input, &i, qflag, old_qflag);
			qflag = 0;
		}
		printf("input[%zd] = %c\n", i, input[i]);
		i++;
	}
	return (input);
}
