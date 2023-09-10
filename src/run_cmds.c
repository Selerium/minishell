/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:53:08 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/09 17:11:32 by jadithya         ###   ########.fr       */
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

int	set_redir_counts(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (1);
}

void	set_redirects(t_chunk *cmd)
{
	int	i;

	i = 0;
	(void) i;
	(void) cmd;
	// cmd->fds_in = malloc (sizeof(int) * set_redir_counts(cmd->redir_in));
	// cmd->fds_out = malloc (sizeof(int) * set_redir_counts(cmd->redir_out));
	// while (cmd->redir_in[i])
	// {
	// 	cmd->fds_in[i] = open(cmd->redir_in[i], O_RDONLY);
	// 	i++;
	// }
	// cmd->fds_in = malloc (sizeof(int) * 5);
	// cmd->fds_out = malloc (sizeof(int) * 5);
	// cmd->fds_in[0] = open(cmd->redir_in[0], O_RDONLY);
	// cmd->fds_out[0] = open(cmd->redir_out[0], O_WRONLY);
	// dup2(cmd->fds_in[i], STDIN_FILENO);
	// dup2(cmd->fds_out[i], STDOUT_FILENO);
}

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
	(void) shell;
	(void) cmd;
	(void) i;
	close_pipes(shell);
}

void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell)
{
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		run_env(shell);
	if (ft_strncmp(cmd[0], "export", 6) == 0)
	{
		run_export(cmd, shell);
		exit(0);
	}
	if (ft_strncmp(cmd[0], "unset", 5) == 0)
		run_unset(cmd[1], shell);
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		run_echo(cmd);
	if (ft_strncmp(cmd[0], "exit", 4) == 0)
		run_exit(cmd[1]);
	if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		run_pwd();
	if (ft_strncmp(cmd[0], "cd", 2) == 0)
		run_cd(cmd);
	execve(cmdpath, cmd, envs);
}

void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i)
{
	int		n;
	char	**envs;
	char	*hold;
	t_env	*temp;
	char	*cmdpath;

	set_child_handlers(shell);
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
	envs[n] = NULL;
	cmdpath = ft_findcmd(cmd->cmd[0], shell->envs);
	set_redirects(cmd);
	close_unneededs(cmd, shell, i);
	ft_execve(cmdpath, cmd->cmd, envs, shell);
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
	while (shell->processes[++i])
		waitpid(shell->processes[i], &shell->exit_code, 0);
	free (shell->processes);
}
