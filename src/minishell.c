/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 19:25:47 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	our_readline(t_minishell *shell)
{
	printf("\e[34m");
	shell->str = readline("\e[0m\e[33;1mhi bestie $>\e[0m ");
	add_history(shell->str);
}

void	print_welcome(int ac, char **av)
{
	int		startfile;
	char	*text;

	(void) ac;
	(void) av;
	startfile = open("src/.startfile", O_RDONLY, 0644);
	if (startfile <= 0)
	{
		printf("Missing startup text file. Create your own if you'd like.\n\n");
		return ;
	}
	text = get_next_line(startfile);
	while (text)
	{
		printf("%s", text);
		free(text);
		text = get_next_line(startfile);
	}
	close(startfile);
}

int	run_single_cmd_mini(t_chunk *cmds, t_minishell *shell, char *cmd)
{
	if (ft_strncmp(cmds->cmd[0], "unset", 6) == 0)
	{
		if (!set_redirects(cmds, shell))
			return (1);
		run_unset(cmds->cmd[1], shell, true);
	}
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
	{
		if (!set_redirects(cmds, shell))
			return (1);
		return (single_exit(cmds, shell->envs, cmd));
	}
	else if (ft_strncmp(cmds->cmd[0], "cd", 3) == 0)
	{
		if (!set_redirects(cmds, shell))
			return (1);
		run_cd(cmds->cmd, true);
	}
	else
	{
		wrap_free(cmd);
		return (0);
	}
	return (1);
}

int	run_single_cmd(t_chunk *cmds, t_minishell *shell)
{
	char	*cmd;

	cmd = NULL;
	g_exitcode = 0;
	if (cmds->cmd && cmds->cmd[0] && cmds->cmd[1])
		cmd = ft_strdup(cmds->cmd[1]);
	if (!cmds->cmd || !cmds->cmd[0])
		return (0);
	if (ft_strncmp(cmds->cmd[0], "export", 7) == 0)
	{
		if (!set_redirects(cmds, shell))
			return (1);
		wrap_export(cmds->cmd, shell);
	}
	else if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
	{
		if (!set_redirects(cmds, shell))
			return (1);
		run_env(shell, true);
	}
	else if (run_single_cmd_mini(cmds, shell, cmd) == 0)
		return (0);
	wrap_free(cmd);
	free_cmd(cmds);
	return (1);
}

int	g_exitcode;

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	print_welcome(argc, argv);
	shell.envs = create_envs(env, &shell);
	set_handlers(&shell);
	shell.flag = 1;
	while (shell.flag)
	{
		our_readline(&shell);
		if (!shell.str)
			break ;
		if (ft_strlen(shell.str) == 0)
			continue ;
		if (is_syntax_valid(shell.str) == false)
			continue ;
		fill_struct(&shell);
		set_num_chunks(shell.cmds, shell.envs, &shell);
		if (shell.num_chunks == 1 && run_single_cmd(shell.cmds, &shell))
			continue ;
		shell.fds = create_fds(&shell);
		shell.processes = ft_calloc (sizeof(int), shell.num_chunks);
		run_cmd(shell.cmds, &shell);
		close_run(&shell);
	}
	free_envs(shell.envs);
}
