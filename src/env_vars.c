/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:52:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/09 20:51:59 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
*	handles setting the env vars, freeing, printing them
*/

#include"../include/minishell.h"

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
*	free the envs list safely (i think).
*/
void	free_envs(t_env *envs)
{
	t_env	*next;

	printf("%s", envs->name);
	while (envs)
	{
		free(envs->name);
		free(envs->value);
		next = envs->next;
		free(envs);
		envs = next;
	}
}
