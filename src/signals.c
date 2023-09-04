/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:51:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/08/17 10:30:08 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/readline.h>
#include <signal.h>

void	sigint_handler(int x)
{
	(void) x;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	set_handlers(t_minishell *shell)
{
	shell->signal_list.ctrl_c = signal(SIGINT, sigint_handler);
	shell->signal_list.ctrl_z = signal(SIGTSTP, SIG_IGN);
	shell->signal_list.ctrl_slash = signal(SIGQUIT, SIG_IGN);
}

void	set_child_handlers(t_minishell *shell)
{
	signal(SIGINT, shell->signal_list.ctrl_c);
	signal(SIGTSTP, shell->signal_list.ctrl_z);
	signal(SIGQUIT, shell->signal_list.ctrl_slash);
}
