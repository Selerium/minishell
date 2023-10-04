/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:12:37 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 19:00:25 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	close_pipes(t_minishell *shell)
{
	int	n;

	n = -1;
	while (++n < shell->num_chunks)
	{
		close(shell->fds[n][READ]);
		close(shell->fds[n][WRITE]);
	}
}

void	close_unneededs(t_chunk *cmd, t_minishell *shell, int i)
{
	(void) cmd;
	(void) i;
	close_pipes(shell);
	unlink(".heredoc.tmp");
}

void	check_to_free_envs(t_chunk *cmd, char **envs, t_minishell *shell)
{
	int		i;

	if ((ft_strncmp(cmd->cmd[0], "env", 3) == 0
			|| ft_strncmp(cmd->cmd[0], "export", 6) == 0
			|| ft_strncmp(cmd->cmd[0], "unset", 6) == 0
			|| ft_strncmp(cmd->cmd[0], "echo", 5) == 0
			|| ft_strncmp(cmd->cmd[0], "exit", 5) == 0
			|| ft_strncmp(cmd->cmd[0], "pwd", 4) == 0
			|| ft_strncmp(cmd->cmd[0], "cd", 3) == 0))
	{
		free_fds(shell->fds, shell->num_chunks);
		if (shell->processes)
			free(shell->processes);
		if (envs)
		{
			i = 0;
			while (envs[i])
				free(envs[i++]);
			free(envs);
		}
		if (ft_strncmp(cmd->cmd[0], "env", 3) != 0)
			free_envs(shell->envs);
	}
}

void	print_exit(char **envs, t_minishell *shell, char *error, int errnum)
{
	int	i;

	i = 0;
	(void) errnum;
	if (envs)
	{
		while (envs[i])
			free(envs[i++]);
		free(envs);
	}
	free_envs(shell->envs);
	free_cmd(shell->cmds);
	free_shell(shell);
	perror(error);
	exit(errnum);
}

void	close_fds(t_minishell *shell, int *fds, int n)
{
	int		i;
	t_chunk	*hold;

	hold = shell->cmds;
	while (hold)
	{
		i = 0;
		while (i < n)
		{
			close (fds[i]);
			i++;
		}
		hold = hold->next;
	}
}