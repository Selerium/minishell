/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:25:13 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/04 18:13:48 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	handle_redirection(char *input, t_flag *flag, size_t *i, char n)
{
	int	count;

	count = 0;
	if ((*flag).redir == false)
		return ;
	flag->redir = false;
	while (input[(*i)] == n)
	{
		count++;
		(*i)++;
	}
	if (count > 2)
		return ;
	while (input[*i] && check_space(input[*i]))
		(*i)++;
	if (ft_strchr("<>|", input[*i]) == NULL && input[*i] != '\0')
		flag->redir = true;
	(*i)--;
}

void	handle_quotes(char *input, t_flag *flag, size_t *i, char n)
{
	flag->quote = false;
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == n)
		{
			flag->quote = true;
			break ;
		}
		(*i)++;
	}
	if (input[*i] == '\0')
		(*i)--;
}

void	handle_pipes(char *input, t_flag *flag, size_t *i)
{
	size_t	tmp;
	size_t	count;

	flag->pipe = false;
	if ((*i) == 0)
		return ;
	tmp = (*i)++ - 1;
	count = 0;
	while (input[*i] && check_space(input[*i]))
		(*i)++;
	if (ft_strchr("|", input[*i]) == NULL && input[*i] != '\0')
		count++;
	while (tmp != 0 && tmp - 1 <= 0 && check_space(input[tmp]))
		tmp--;
	if (ft_strchr("|", input[tmp]) == NULL)
		count++;
	if (count == 2)
		flag->pipe = true;
	(*i)--;
}
