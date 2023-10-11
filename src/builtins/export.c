/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 15:46:52 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
*	replaces the export function for the env vars.
*
*	>	goes through env, breaks if reached same variable or name < env[i].
*	>	replaces env[i] w/ name=value, or adds to list right before it.
*	>	if name is biggest name, adds to the end of the env list.

*	>	(hell no we're not sorting)
*/

bool	check_export_cmd(char *cmd)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	if (cmd[0] == '=' || ft_isdigit(cmd[0]))
		return (false);
	while (cmd[i])
	{
		if (cmd[i] == '=' && !flag)
			flag = true;
		else if (cmd[i] == '=')
			return (false);
		else if (!flag && !ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	wrap_export(char **cmd, t_minishell *shell)
{
	int	i;

	if (!cmd[1])
		return (print_envs(shell->envs, false));
	i = 1;
	while (cmd[i])
	{
		if (check_export_cmd(cmd[i]))
			run_export(cmd[i], shell, false);
		else
			printf("export: incorrect variable declaration\n");
		i++;
	}
}

void	env_exists_mini(t_env *iter_env, t_env *hold)
{
	wrap_free(iter_env->name);
	wrap_free(iter_env->value);
	iter_env->name = ft_strdup(hold->name);
	iter_env->value = ft_strdup(hold->value);
	free_envs(hold);
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
		if (envcondition(iter_env->name, cmd))
		{
			flag = true;
			break ;
		}
		iter_env = iter_env->next;
	}
	if (!flag || !cmd)
		return (false);
	hold = add_env(cmd, shell);
	if (!hold->value || is_env)
	{
		free_envs(hold);
		return (true);
	}
	env_exists_mini(iter_env, hold);
	return (true);
}

void	run_export(char *cmd, t_minishell *shell, bool is_env)
{
	t_env	*iter_env;
	t_env	*new_env;
	int		i;
	int		flag;

	if (env_exists(cmd, shell, is_env))
		return ;
	i = 0;
	flag = 1;
	while (cmd[i] && cmd[i] != '=')
		if (cmd[i++] == '-')
			flag = 0;
	if (!flag)
	{
		g_exitcode = 1;
		return (perror("Invalid environment variable declaration\n"));
	}
	iter_env = shell->envs;
	while (iter_env && iter_env->next)
		iter_env = iter_env->next;
	new_env = add_env(cmd, shell);
	if (iter_env)
		iter_env->next = new_env;
	else
		shell->envs = new_env;
}
