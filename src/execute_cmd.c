/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:50:32 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 16:14:53 by jadithya         ###   ########.fr       */
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

void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i)
{
	int		n;
	char	**envs;
	char	*hold;
	t_env	*temp;
	char	*cmdpath;

	set_child_handlers(shell);
	temp = shell->envs;
	envs = ft_calloc (sizeof(char *), (shell->num_envs + 1));
	if (!envs)
		printf("exec cmd - ft_calloc eror\n");
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
	check_to_free_envs(cmd, envs, shell);
	if (!cmdpath)
		print_exit(envs, shell, "Command not found", 127);
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
	exit(127);
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
