/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:52:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 18:09:37 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
*	handles setting the env vars, freeing, printing them
*/

#include "../include/minishell.h"

t_env	*get_env(char *name, t_minishell shell)
{
	t_env	*temp;

	temp = shell.envs;
	while (temp)
	{
		if (ft_strncmp(temp->name, name, ft_strlen(name) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*add_env(char *str, t_minishell *shell)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = ft_calloc (sizeof(t_env), 1);
	if (!new_env)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new_env->name = ft_substr(str, 0, i);
	if (str[i] == '=' && !str[i + 1])
		new_env->value = ft_strdup("");
	else if (shell->cmds && str[i] == '=' && ft_strchr(&str[i + 1], '$'))
		new_env->value = expand_env(&str[i], *shell, 0);
	else if (str[i] != '=')
		new_env->value = NULL;
	else
		new_env->value = ft_substr(str, i + 1, ft_strlen(str) - i);
	new_env->next = NULL;
	return (new_env);
}

t_env	*create_envs(char **env, t_minishell *shell)
{
	t_env	*start;
	t_env	*next;
	int		i;

	i = 0;
	shell->cmds = NULL;
	if (! env || !env[0])
		return (NULL);
	start = add_env(env[i], shell);
	next = start;
	while (env[++i] && next)
	{
		next->next = add_env(env[i], shell);
		next = next->next;
	}
	if (!next)
		return (NULL);
	return (start);
}

void	print_envs(t_env *envs, bool is_env)
{
	while (envs)
	{
		if (is_env)
		{
			if (envs->value && envs->name)
			{
				if (ft_strlen(envs->value))
					printf("%s=%s\n", envs->name, envs->value);
				else
					printf("%s=\"\"\n", envs->name);
			}
		}
		else
		{
			printf("declare -x ");
			printf("%s", envs->name);
			if (envs->value && ft_strlen(envs->value))
				printf("=\"%s\"\n", envs->value);
			else if (envs->value)
				printf("=\"\"\n");
			else
				printf("\n");
		}
		envs = envs->next;
	}
}

/**
*	free the envs list safely (i think).
*/
void	free_envs(t_env *envs)
{
	t_env	*next;

	while (envs)
	{
		if (envs->name)
			free(envs->name);
		if (envs->value)
			free(envs->value);
		next = envs->next;
		free(envs);
		envs = next;
	}
}
