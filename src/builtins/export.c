/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/16 21:37:02 by jadithya         ###   ########.fr       */
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

	iter_env = shell->envs;
	while (iter_env->next)
		iter_env = iter_env->next;
	new_env = add_env(cmd[1]);
	printf("%s = %s\n", new_env->name, new_env->value);
	iter_env->next = new_env;
	if (!parent)
		exit(0);
}
