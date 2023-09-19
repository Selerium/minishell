/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:53:08 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/16 18:53:19 by jadithya         ###   ########.fr       */
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

	fds = (int **) malloc (sizeof(int *) * shell->num_chunks);
	i = 0;
	while (i < shell->num_chunks)
	{
		fds[i] = (int *) malloc (sizeof(int) * 2);
		pipe(fds[i]);
		i++;
	}
	return (fds);
}

//check if pipe creation is failing
//check if processes malloc fails
//check if processes forking fails
void	run_cmd(t_chunk *cmds, t_minishell *shell)
{
	t_chunk	*iter_cmd;
	int		i;

	iter_cmd = cmds;
	i = 0;
	while (iter_cmd)
	{
		set_redirects(iter_cmd);
		shell->processes[i] = fork();
		if (shell->processes[i] == 0)
		{
			if (i != 0)
				dup2(shell->fds[i][READ], STDIN_FILENO);
			if (i != shell->num_chunks - 1)
				dup2(shell->fds[i + 1][WRITE], STDOUT_FILENO);
			execute_cmd(iter_cmd, shell, i);
		}
		iter_cmd = iter_cmd->next;
		i++;
	}
	i = -1;
	close_pipes(shell);
	while (++i < shell->num_chunks)
		waitpid(shell->processes[i], &shell->exit_code, 0);
	free (shell->processes);
}
