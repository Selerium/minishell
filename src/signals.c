/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:51:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 14:50:24 by jadithya         ###   ########.fr       */
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

bool	envcondition(char *a, char *b)
{
	char	*cmd;
	int		n;

	n = 0;
	while (b[n] && b[n] != '=')
		n++;
	cmd = ft_substr(b, 0, n);
	if (ft_strncmp(a, cmd, ft_strlen(a)) == 0
		&& ft_strlen(a) == ft_strlen(cmd))
	{
		wrap_free(cmd);
		return (true);
	}
	wrap_free(cmd);
	return (false);
}
