/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 19:46:42 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/history.h>

/**
*	free the envs list safely (i think).
*/
void	free_envs(t_env *envs)
{
	t_env	*next;

	while (envs)
	{
		free(envs->name);
		free(envs->value);
		next = envs->next;
		free(envs);
		envs = next;
	}
}

t_env	*add_env(char *str)
{
	t_env	*new_env;

	new_env = malloc (sizeof(t_env));
	if (!new_env)
		return (NULL);
}

t_env	*create_envs(char **env)
{
	t_env	*start;
	t_env	*next;

	
}

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
	flag = 1;
	envs = create_envs(env);
	while (flag)
	{
		out = readline("hi bestie $> ");
		// readline("hi bestie $> ");
		array_out = ft_split(out, ' ');
		pwd(env);
		ms_cd(array_out);
		// pwd();
		
	}
}
 