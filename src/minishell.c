/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/22 16:08:12 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	while (true)
	{
		readline("hi bestie $> ");
		pwd();
		
	}
}
