/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:46:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 22:38:28 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	wrap_free(void *item)
{
	if (item)
		free(item);
}

void	free_cmd(t_chunk *cmd)
{
	int		i;
	t_chunk	*hold;

	while (cmd)
	{
		i = 0;
		while (cmd->cmd[i])
			free(cmd->cmd[i++]);
		wrap_free(cmd->cmd);
		free_redirs(cmd);
		wrap_free(cmd->fds_in);
		wrap_free(cmd->fds_out);
		hold = cmd->next;
		free(cmd);
		cmd = hold;
	}
}

void	free_redirs(t_chunk *cmd)
{
	int	i;

	i = 0;
	if (cmd->redir_in)
		while (cmd->redir_in[i])
			free(cmd->redir_in[i++]);
	wrap_free(cmd->redir_in);
	wrap_free(cmd->redir_in_type);
	i = 0;
	if (cmd->redir_out)
		while (cmd->redir_out[i])
			free(cmd->redir_out[i++]);
	wrap_free(cmd->redir_out);
	wrap_free(cmd->redir_out_type);
}

void	free_fds(int **fds, int n)
{
	int	i;

	i = 0;
	while (i < n && fds[i])
		free(fds[i++]);
	wrap_free(fds);
}

void	free_shell(t_minishell *shell)
{
	free_fds(shell->fds, shell->num_chunks);
	wrap_free(shell->processes);
}
