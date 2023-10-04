/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:53:08 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 19:02:56 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	set_num_chunks(t_chunk *cmd, t_env *env, t_minishell *shell)
{
	shell->num_chunks = 0;
	shell->num_envs = 0;
	while (cmd)
	{
		shell->num_chunks++;
		cmd = cmd->next;
	}
	while (env)
	{
		shell->num_envs++;
		env = env->next;
	}
}

int	**create_fds(t_minishell *shell)
{
	int	**fds;
	int	i;

	fds = (int **) ft_calloc (sizeof(int *), shell->num_chunks);
	i = 0;
	while (i < shell->num_chunks)
	{
		fds[i] = (int *) ft_calloc (sizeof(int), 2);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

t_chunk	*free_iter(t_chunk *cmd)
{
	int		i;
	t_chunk	*hold;

	i = 0;
	while (cmd->cmd && cmd->cmd[i])
		free(cmd->cmd[i++]);
	free(cmd->cmd);
	i = 0;
	while (cmd->redir_in && cmd->redir_in[i])
		free (cmd->redir_in[i++]);
	free(cmd->redir_in);
	i = 0;
	while (cmd->redir_out && cmd->redir_out[i])
		free (cmd->redir_out[i++]);
	if (cmd->redir_out)
		free(cmd->redir_out);
	if (cmd->redir_in_type)
		free(cmd->redir_in_type);
	if (cmd->redir_out_type)
		free(cmd->redir_out_type);
	if (cmd->fds_in)
		free(cmd->fds_in);
	if (cmd->fds_out)
		free(cmd->fds_out);
	hold = cmd->next;
	free (cmd);
	return (hold);
}

//check if pipe creation is failing
//check if processes ft_calloc fails
//check if processes forking fails
void	run_cmd(t_chunk *cmds, t_minishell *shell)
{
	t_chunk	*iter_cmd;
	int		i;

	iter_cmd = cmds;
	i = 0;
	while (iter_cmd)
	{
		shell->processes[i] = fork();
		if (shell->processes[i] == 0)
		{
			if (i != 0)
				dup2(shell->fds[i][READ], STDIN_FILENO);
			if (i != shell->num_chunks - 1)
				dup2(shell->fds[i + 1][WRITE], STDOUT_FILENO);
			set_redirects(iter_cmd, shell);
			execute_cmd(iter_cmd, shell, i);
		}
		shell->cmds = shell->cmds->next;
		iter_cmd = free_iter(iter_cmd);
		i++;
	}
	i = -1;
	close_pipes(shell);
	while (++i < shell->num_chunks)
		waitpid(shell->processes[i], &g_exitcode, 0);
	if (WIFEXITED(g_exitcode))
		g_exitcode = WEXITSTATUS(g_exitcode);
}
