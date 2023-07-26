/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:51:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 20:10:54 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/readline.h>

void	sigint_handler(int x)
{
	(void) x;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_handlers(void)
{
	signal(SIGINT, SIG_IGN);
}

void	set_child_handlers(void)
{
	signal(SIGINT, sigint_handler);
}
