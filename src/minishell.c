/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/22 15:55:20 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/

int	main(int argc, char **argv, char **env)
{
	t_env	*envs;

	(void) argc;
	(void) argv;
	envs = fill_vars(env);
	while (true)
	{
		readline("hi bestie $> ");
		pwd(env);
	}
}
