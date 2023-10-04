/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 19:06:01 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	replaces the export function for the env vars.
*
*	>	goes through env, breaks if reached same variable or name < env[i].
*	>	replaces env[i] w/ name=value, or adds to list right before it.
*	>	if name is biggest name, adds to the end of the env list.
*/

void	run_export(char **cmd, t_minishell *shell, bool parent)
{
	t_env	*iter_env;
	t_env	*new_env;
	int		i;
	int		flag;

	(void) parent;
	i = 0;
	flag = 0;
	if (!cmd[1])
	{
		print_envs(shell->envs, true);
		return ;
	}
	while (cmd[1][i])
	{
		if (cmd[1][i] == '=')
			flag = 1;
		i++;
	}
	if (!flag)
		return ;
	iter_env = shell->envs;
	while (iter_env->next)
		iter_env = iter_env->next;
	new_env = add_env(cmd[1]);
	iter_env->next = new_env;
}
