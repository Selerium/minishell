/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 21:55:44 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void	our_readline(t_minishell *shell)
{
	char	*text;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("\e[34m");
	text = ft_strjoin(cwd, "\e[0m\e[33;1m:hi bestie $>\e[0m ");
	shell->str = readline(text);
	free(cwd);
	free(text);
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

int	run_single_cmd(t_chunk *cmds, t_minishell *shell)
{
	char	*cmd;

	cmd = NULL;
	if (cmds->cmd[1])
		cmd = ft_strdup(cmds->cmd[1]);
	if (ft_strncmp(cmds->cmd[0], "export", 7) == 0)
		run_export(cmds->cmd, shell, true);
	else if (ft_strncmp(cmds->cmd[0], "env", 4) == 0)
		run_env(shell, true);
	else if (ft_strncmp(cmds->cmd[0], "cd", 3) == 0)
		run_cd(cmds->cmd, true);
	else if (ft_strncmp(cmds->cmd[0], "unset", 6) == 0)
		run_unset(cmds->cmd[1], shell, true);
	else if (ft_strncmp(cmds->cmd[0], "exit", 5) == 0)
		single_exit(cmds, shell->envs, cmd);
	else
	{
		wrap_free(cmd);
		return (0);
	}
	wrap_free(cmd);
	free_cmd(cmds);
	g_exitcode = 0;
	return (1);
}

int	g_exitcode;

int	main(int argc, char **argv, char **env)
{
	t_minishell	shell;

	print_welcome(argc, argv);
	shell.envs = create_envs(env);
	set_handlers(&shell);
	shell.flag = 1;
	while (shell.flag)
	{
		our_readline(&shell);
		if (!shell.str)
			break ;
		if (ft_strlen(shell.str) == 0)
			continue ;
		if (is_syntax_valid(shell.str) == true)
			fill_struct(&shell);
		set_num_chunks(shell.cmds, shell.envs, &shell);
		if (shell.num_chunks == 1 && run_single_cmd(shell.cmds, &shell))
			continue ;
		shell.fds = create_fds(&shell);
		shell.processes = ft_calloc (sizeof(int), shell.num_chunks);
		run_cmd(shell.cmds, &shell);
		free_shell(&shell);
	}
	free_envs(shell.envs);
}
