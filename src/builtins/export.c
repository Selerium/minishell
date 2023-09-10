/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/09 17:12:22 by jadithya         ###   ########.fr       */
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

void	run_export(char **cmd, t_minishell *shell)
{
	t_env	*i;
	t_env	*left;
	t_env	*right;

	i = shell->envs;
	while (i)
	{
		if (ft_strncmp(i->name, cmd[1], ft_strlen(i->name)) == 0)
		{
			i->value = ft_substr(cmd[1], ft_strlen(i->name),
					ft_strlen(cmd[1]) - ft_strlen(i->name));
			exit(0);
		}
		else
		{
			if (ft_strncmp(i->name, cmd[1], ft_strlen(i->name)) < 0)
				left = i;
			if (ft_strncmp(i->name, cmd[1], ft_strlen(i->name)) > 0)
				right = i;
			if (left && right)
				break ;
		}
		left->next = add_env(cmd[1]);
		left->next->next = right;
	}
}
