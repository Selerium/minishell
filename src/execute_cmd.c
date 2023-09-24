/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:50:32 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/24 23:15:15 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	dup_redirects(t_chunk *cmd)
{
	int	i;

	if (cmd->redir_out)
	{
		i = set_redir_counts(cmd->redir_out);
		dup2(cmd->fds_out[i - 1], STDOUT_FILENO);
		while (--i >= 0)
			close(cmd->fds_out[i]);
	}
	if (cmd->redir_in)
	{
		i = set_redir_counts(cmd->redir_in);
		dup2(cmd->fds_in[i - 1], STDIN_FILENO);
		while (--i >= 0)
			close(cmd->fds_in[i]);
	}
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
	unlink(".heredoc.tmp");
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
	dup_redirects(cmd);
	close_unneededs(cmd, shell, i);
	ft_execve(cmdpath, cmd->cmd, envs, shell);
}

void	run_minishell(char *cmdpath, char **cmd, char **envs, t_minishell shell)
{
	char	*num;
	int		val;
	int		i;

	i = 0;
	while (shell.envs)
	{
		if (ft_strncmp(shell.envs->name, "SHLVL", 6) == 0)
		{
			val = ft_atoi(shell.envs->value) + 1;
			num = ft_itoa(val, '0', 0);
			free(envs[i]);
			envs[i] = ft_strjoin("SHLVL=", num);
			printf("here %s\n", envs[i]);
			break ;
		}
		shell.envs = shell.envs->next;
		i++;
	}
	execve(cmdpath, cmd, envs);
	perror("Command not found");
	exit(-1);
}

void	check_to_free_envs(char *cmd, char **envs, t_minishell *shell, char *cmdpath)
{
	(void) shell;
	(void) envs;
	(void) cmdpath;

	if ((ft_strncmp(cmd, "env", 3) == 0
			|| ft_strncmp(cmd, "export", 6) == 0
			|| ft_strncmp(cmd, "unset", 6) == 0
			|| ft_strncmp(cmd, "echo", 5) == 0
			|| ft_strncmp(cmd, "exit", 5) == 0
			|| ft_strncmp(cmd, "pwd", 4) == 0
			|| ft_strncmp(cmd, "cd", 3) == 0))
	{
		// free_fds(shell->fds, shell->num_chunks);
		// if (shell->processes)
		// 	free(shell->processes);
		// if (cmdpath)
		// 	free(cmdpath);
		// if (envs)
		// {
		// 	i = 0;
		// 	while (envs[i])
		// 		free(envs[i++]);
		// 	free(envs);
		// }
		// free_envs(shell->envs);
	}
}

void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell)
{
	check_to_free_envs(cmd[0], envs, shell, cmdpath);
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		run_env(shell, false);
	if (ft_strncmp(cmd[0], "export", 6) == 0)
	{
		run_export(cmd, shell, false);
		exit(0);
	}
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		run_unset(cmd[1], shell, false);
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		run_echo(cmd);
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		run_exit(cmd[1]);
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		run_pwd();
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		run_cd(cmd, false);
	if (ft_strncmp(cmd[0], "./minishell", 12) == 0)
		run_minishell(cmdpath, cmd, envs, *shell);
	execve(cmdpath, cmd, envs);
	perror("Command not found");
	exit(-1);
}
