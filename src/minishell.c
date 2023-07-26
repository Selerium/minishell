/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 16:59:46 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/

int	main(int argc, char **argv, char **env)
{
	// t_env	*envs;
	char *out;
	char **array_out;

	(void) argc;
	(void) argv;
	// envs = fill_vars(env);
	while (true)
	{
		out = readline("hi bestie $> ");
		// readline("hi bestie $> ");
		array_out = ft_split(out, ' ');
		pwd(env);
		ms_cd(array_out);
		// pwd();
		
	}
}
