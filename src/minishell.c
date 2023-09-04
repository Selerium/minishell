/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/08/31 10:05:12 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	free_cmd(t_chunk *cmd)
{
	int		i;
	t_chunk	*hold;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
		// i = 0;
		// while (cmd->redir_in[i])
		// 	free(cmd->redir_in[i++]);
		// i = 0;
		// while (cmd->redir_out[i])
		// 	free(cmd->redir_out[i++]);
		hold = cmd->next;
		free(cmd);
		cmd = hold;
	}
}

void	free_fds(int **fds, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(fds[i++]);
	free(fds);
}

void	free_shell(t_minishell *shell)
{
	free_cmd(shell->cmds);
	free_envs(shell->envs);
	free_fds(shell->fds, shell->num_chunks);
	free(shell->processes);
}

int	our_readline(t_minishell *shell)
{
	char	*text;

	(void) shell;
	text = readline("hi bestie $> ");
	if (text)
	{
		shell->str = text;
		return (1);
	}
	return (0);
}

t_chunk	*test_cmds(void)
{
	t_chunk	*cmd1;
	t_chunk	*cmd2;
	t_chunk	*cmd3;

	cmd1 = malloc (sizeof(t_chunk));
	cmd2 = malloc (sizeof(t_chunk));
	cmd3 = malloc (sizeof(t_chunk));
	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = NULL;
	cmd1->args = ft_split("ls -la", ' ');
	cmd2->args = ft_split("cat", ' ');
	cmd3->args = ft_split("ls", ' ');
	return (cmd1);
}

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/
int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	(void) argc;
	(void) argv;
	shell.envs = create_envs(env);
	print_envs(shell.envs);
	set_handlers(&shell);
	shell.flag = 1;
	while (shell.flag)
	{
		shell.str = readline("hi bestie $> ");
		if (shell.str)
		{
			add_history(shell.str);
			set_flags(shell.str);
			shell.cmds = test_cmds();
			set_num_chunks(shell.cmds, &shell);
			run_cmd(shell.cmds, &shell);
			free_cmd(shell.cmds);
		}
		else
			shell.flag = 0;
	}
	free_envs(shell.envs);
}
 