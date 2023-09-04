/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deboog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:46:54 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/04 18:09:57 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	print_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		printf("str[%ld] = [%s]\n", i, str[i]);
		i++;
	}
}

void	deboog(t_chunk *chunk)
{
	size_t	i;
	size_t	j;
	size_t	cmd;

	while (chunk)
	{
		i = 0;
		j = 0;
		cmd = 0;
		while (chunk->cmd && chunk->cmd[cmd])
		{
			printf("cmd[%ld] = [%s]\n", cmd, chunk->cmd[cmd]);
			cmd++;
		}
		while ((chunk->redir_out && chunk->redir_out[i] != NULL)
			|| (chunk->redir_out_type && chunk->redir_out_type[i]))
		{
			printf("redir_out[%ld] = [%s] | type = %d\n", i, chunk->redir_out[i],
				chunk->redir_out_type[i]);
			i++;
		}
		while ((chunk->redir_in && chunk->redir_in[j] != NULL)
			|| (chunk->redir_in_type && chunk->redir_in_type[j]))
		{
			printf("redir_in[%ld] = [%s] | type = %d\n", j, chunk->redir_in[j],
				chunk->redir_in_type[j]);
			j++;
		}
		printf("---------------------------------------------------------\n");
		chunk = chunk->next;
	}
}
