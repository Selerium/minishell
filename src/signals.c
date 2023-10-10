/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:51:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 22:54:17 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	sigint_handler(int x)
{
	(void) x;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\e[34m");
	rl_redisplay();
	g_exitcode = 127;
}

void	set_handlers(t_minishell *shell)
{
	shell->signal_list.ctrl_c = signal(SIGINT, sigint_handler);
	shell->signal_list.ctrl_slash = signal(SIGQUIT, SIG_IGN);
}

void	set_child_handlers(t_minishell *shell)
{
	signal(SIGINT, shell->signal_list.ctrl_c);
	signal(SIGQUIT, shell->signal_list.ctrl_slash);
}

void	special_free(t_minishell *shell)
{
	free_cmd(shell->cmds);
	free_envs(shell->envs);
	free_fds(shell->fds, shell->num_chunks);
	wrap_free(shell->processes);
	exit(g_exitcode);
}
