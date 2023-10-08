/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/08 18:23:24 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>

/**
*	replaces the export function for the env vars.
*
*	>	goes through env, breaks if reached same variable or name < env[i].
*	>	replaces env[i] w/ name=value, or adds to list right before it.
*	>	if name is biggest name, adds to the end of the env list.

*	>	(hell no we're not sorting)
*/

void	wrap_export(char **cmd, t_minishell *shell, bool parent)
{
	int	i;

	i = 1;
	if (!cmd[1])
		return (print_envs(shell->envs, false));
	while (cmd[i])
		run_export(cmd[i++], shell, parent, false);
}

bool	env_exists(char *cmd, t_minishell *shell, bool is_env)
{
	t_env	*iter_env;
	t_env	*hold;
	bool	flag;

	iter_env = shell->envs;
	flag = false;
	while (iter_env && !flag)
	{
		if (ft_strncmp(iter_env->name, cmd, ft_strlen(iter_env->name)) == 0)
		{
			flag = true;
			break ;
		}
		iter_env = iter_env->next;
	}
	if (!flag || !cmd)
		return (false);
	hold = add_env(cmd);
	if (!hold->value || is_env)
	{
		free_envs(hold);
		return (true);
	}
	wrap_free(iter_env->name);
	wrap_free(iter_env->value);
	iter_env->name = ft_strdup(hold->name);
	iter_env->value = ft_strdup(hold->value);
	free_envs(hold);
	return (true);
}

void	run_export(char *cmd, t_minishell *shell, bool parent, bool is_env)
{
	t_env	*iter_env;
	t_env	*new_env;
	int		i;
	int		flag;

	(void) parent;
	if (env_exists(cmd, shell, is_env))
		return ;
	i = 0;
	flag = 1;
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i] == '-')
			flag = 0;
		i++;
	}
	if (!flag)
		return ((void) printf("Invalid environment variable declaration\n"));
	iter_env = shell->envs;
	while (iter_env && iter_env->next)
		iter_env = iter_env->next;
	new_env = add_env(cmd);
	iter_env->next = new_env;
}
