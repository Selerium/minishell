/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:51:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/27 19:36:51 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/readline.h>

void	sigint_handler(int x)
{
	(void) x;
	write(1, "\n", 1);
}

void	set_handlers(void)
{
	signal(SIGINT, sigint_handler);
}

void	set_child_handlers(void)
{
	signal(SIGINT, sigint_handler);
}
