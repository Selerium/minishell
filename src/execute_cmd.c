/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:50:32 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/06 00:18:12 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <unistd.h>

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

void	make_envs_array(t_env *envs, char **list)
{
	char	*hold;
	int		n;

	n = 0;
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

	set_child_handlers(shell);
	envs = ft_calloc (sizeof(char *), (shell->num_envs + 1));
	if (!envs)
		printf("exec cmd - ft_calloc eror\n");
	make_envs_array(shell->envs, envs);
	cmdpath = ft_findcmd(cmd->cmd[0], shell->envs);
	dup_redirects(cmd);
	close_unneededs(cmd, shell, i);
	check_to_free_envs(cmd, envs, shell);
	if (!cmdpath)
		print_exit(envs, shell, "Command not found", 127);
	ft_execve(cmdpath, cmd->cmd, envs, shell);
}

void	wrap_execve(char *cmdpath, char **cmd, char **envs)
{
	execve(cmdpath, cmd, envs);
	perror("Command not found");
	exit(127);
}

void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell)
{
	if (ft_strncmp(cmd[0], "env", 3) == 0)
		run_env(shell, false);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
	{
		run_export(cmd, shell, false);
		exit(0);
	}
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		run_unset(cmd[1], shell, false);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		run_echo(cmd);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		run_exit(cmd[1]);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		run_pwd();
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		run_cd(cmd, false);
	else if (ft_strncmp(cmd[0], "./minishell", 12) == 0)
		run_minishell(cmdpath, cmd, envs, *shell);
	else
		wrap_execve(cmdpath, cmd, envs);
	free (cmdpath);
	free_cmd(shell->cmds);
	exit(0);
}
