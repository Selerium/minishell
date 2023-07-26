/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 20:18:36 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

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

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	if (cmd)
		free(cmd);
}

t_env	*add_env(char *str)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = malloc (sizeof(t_env));
	if (!new_env)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new_env->name = ft_substr(str, 0, i);
	new_env->value = ft_substr(str, i + 1, ft_strlen(str));
	new_env->next = NULL;
	return (new_env);
}

t_env	*create_envs(char **env)
{
	t_env	*start;
	t_env	*next;
	int		i;

	i = 0;
	start = add_env(env[i]);
	next = start;
	while (env[++i] && next)
	{
		next->next = add_env(env[i]);
		next = next->next;
	}
	if (!next)
		return (NULL);
	return (start);
}

void	print_envs(t_env *envs)
{
	while (envs)
	{
		printf("%s = %s\n", envs->name, envs->value);
		envs = envs->next;
	}
}

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/
int	main(int argc, char **argv, char **env)
{
	int			flag;
	t_minishell	shell;
	char		**array_out;

	(void) argc;
	(void) argv;
	shell.envs = create_envs(env);
	flag = 1;
	set_handlers();
	while (flag)
	{
		shell.str = readline("hi bestie $> ");
		add_history(shell.str);
		array_out = ft_split(shell.str, ' ');
		ms_cd(array_out);
		free_cmd(array_out);
	}
	print_envs(shell.envs);
	free_envs(shell.envs);
}
 