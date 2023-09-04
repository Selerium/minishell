/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:53:08 by jadithya          #+#    #+#             */
/*   Updated: 2023/08/31 15:28:58 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	set_num_chunks(t_chunk *cmd, t_minishell *shell)
{
	shell->num_chunks = 0;
	while (cmd)
	{
		shell->num_chunks++;
		cmd = cmd->next;
	}
}

void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i)
{
	(void) cmd;
	(void) shell;
	(void) i;
	printf("we made it %s\n", cmd->args[0]);
	free_shell(shell);
	exit(0);
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
