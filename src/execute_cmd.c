/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:50:32 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 14:47:47 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	dup_redirects(t_chunk *cmd)
{
	int	i;

	if (cmd->redir_out)
	{
		i = set_redir_counts(cmd->redir_out);
		dup2(cmd->fds_out[i - 1], STDOUT_FILENO);
		while (--i >= 0)
			if (cmd->fds_out[i] >= 0)
				close(cmd->fds_out[i]);
	}
	if (cmd->redir_in)
	{
		i = set_redir_counts(cmd->redir_in);
		dup2(cmd->fds_in[i - 1], STDIN_FILENO);
		while (--i >= 0)
			if (cmd->fds_in[i] >= 0)
				close(cmd->fds_in[i]);
	}
}

void	make_envs_array(t_env *envs, char **list)
{
	char	*hold;
	int		n;

	n = 0;
	if (!envs)
	{
		list = NULL;
		return ;
	}
	while (envs)
	{
		if (!envs->name || !envs->value)
			break ;
		hold = ft_strjoin(envs->name, "=");
		list[n] = ft_strjoin(hold, envs->value);
		free(hold);
		envs = envs->next;
		n++;
	}
	list[n] = NULL;
}

void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i)
{
	char	**envs;
	char	*cmdpath;

	envs = ft_calloc (sizeof(char *), (shell->num_envs + 1));
	if (!envs)
		printf("exec cmd - ft_calloc eror\n");
	make_envs_array(shell->envs, envs);
	if (!cmd->cmd || !cmd->cmd[0])
	{
		close_pipes(shell);
		close_fds(shell, cmd->fds_in, cmd->redir_in_count);
		close_fds(shell, cmd->fds_out, cmd->redir_out_count);
		print_exit(envs, shell, "Invalid input", 1);
	}
	cmdpath = ft_findcmd(cmd->cmd[0], shell->envs);
	dup_redirects(cmd);
	close_pipes(shell);
	close_unneededs(cmd, shell, i, false);
	check_to_free_envs(cmd, envs, shell);
	if (!cmdpath)
		print_exit(envs, shell, "Command not found", 127);
	ft_execve(cmdpath, cmd->cmd, envs, shell);
}

void	wrap_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell)
{
	int	i;

	execve(cmdpath, cmd, envs);
	perror("Command not found");
	free_envs(shell->envs);
	free_cmd(shell->cmds);
	close_pipes(shell);
	i = 0;
	while (envs[i])
		wrap_free(envs[i++]);
	wrap_free(envs);
	wrap_free(shell->processes);
	i = 0;
	while (shell->fds && i < shell->num_chunks && shell->fds[i])
		wrap_free(shell->fds[i++]);
	wrap_free(shell->fds);
	if (cmdpath[0] == '.' || cmdpath[0] == '/')
	{
		wrap_free(cmdpath);
		exit(127);
	}
	printf("%s\n", cmd[0]);
	wrap_free(cmdpath);
	exit(127);
}

void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell)
{
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		run_env(shell, false);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
	{
		wrap_export(cmd, shell);
		free_envs(shell->envs);
	}
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		wrap_unset(cmd, shell, false);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		run_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		wrap_exit(cmd, shell, cmdpath);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		run_pwd(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		run_cd(cmd, false);
	else if (ft_strncmp(cmd[0], "./minishell", 12) == 0)
		run_minishell(cmdpath, cmd, envs, *shell);
	else
		wrap_execve(cmdpath, cmd, envs, shell);
	wrap_free(cmdpath);
	free_cmd(shell->cmds);
	exit(g_exitcode);
}
