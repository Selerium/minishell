/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:46:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/25 16:57:19 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	free_cmd(t_chunk *cmd)
{
	int		i;
	t_chunk	*hold;

	while (cmd)
	{
		i = 0;
		if (cmd->cmd)
		{
			while (cmd->cmd[i])
				free(cmd->cmd[i++]);
			free(cmd->cmd);
		}
		i = 0;
		if (cmd->redir_in)
		{
			while (cmd->redir_in[i])
				free(cmd->redir_in[i++]);
			free(cmd->redir_in);
		}
		i = 0;
		if (cmd->redir_out)
		{
			while (cmd->redir_out[i])
				free(cmd->redir_out[i++]);
			free(cmd->redir_out);
		}
		hold = cmd->next;
		free(cmd);
		cmd = hold;
	}
}

void	free_redirs(t_chunk *cmd)
{
	t_chunk	*hold;

	while (cmd)
	{
		if (cmd->fds_in)
			free(cmd->fds_in);
		if (cmd->fds_out)
			free(cmd->fds_out);
		hold = cmd->next;
		free(cmd);
		cmd = hold;
	}
}

void	free_fds(int **fds, int n)
{
	int	i;

	i = 0;
	while (i < n && fds[i])
		free(fds[i++]);
	if (fds)
		free(fds);
}

void	free_shell(t_minishell *shell)
{
	free_cmd(shell->cmds);
	free_fds(shell->fds, shell->num_chunks);
	if (shell->processes)
		free(shell->processes);
}
