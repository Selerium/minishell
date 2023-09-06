/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:53:08 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/06 10:48:24 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <errno.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i)
{
	int		n;
	char	**envs;
	char	*hold;
	t_env	*temp;
	char	*cmdpath;

	(void) cmd;
	(void) i;
	temp = shell->envs;
	envs = malloc (sizeof(char *) * (shell->num_envs + 1));
	if (!envs)
		printf("exec cmd - malloc eror\n");
	n = 0;
	while (temp)
	{
		hold = ft_strjoin(temp->name, "=");
		envs[n] = ft_strjoin(hold, temp->value);
		free(hold);
		temp = temp->next;
		n++;
	}
	cmdpath = ft_findcmd(cmd->cmd[0], shell->envs);
	execve(cmdpath, cmd->cmd, envs);
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
	int		status;

	shell->fds = create_fds(shell);
	shell->processes = malloc (sizeof(int) * shell->num_chunks);
	iter_cmd = cmds;
	i = 0;
	// pipe(shell->fds[0]);
	// dup2(shell->fds[0][WRITE], STDOUT_FILENO);
	while (iter_cmd)
	{
		// if (i < shell->num_chunks - 1)
		// 	pipe(shell->fds[i + 1]);
		shell->processes[i] = fork();
		if (shell->processes[i] == 0)
		{
			// dup2(shell->fds[i][READ], STDIN_FILENO);
			// if (i != shell->num_chunks - 1)
				// dup2(shell->fds[i + 1][WRITE], STDOUT_FILENO);
			execute_cmd(iter_cmd, shell, i);
		}
		iter_cmd = iter_cmd->next;
		i++;
	}
	i = 0;
	while (i < shell->num_chunks)
	{
		waitpid(shell->processes[i], &status, WEXITED);
		printf("process %d completed with an exit status %d\n", i, WEXITSTATUS(status));
		i++;
	}
	free (shell->processes);
}
