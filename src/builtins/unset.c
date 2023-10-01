/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:30:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/01 14:00:30 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

t_env	*free_single_env(t_env *env)
{
	t_env	*value;

	free(env->name);
	free(env->value);
	value = env->next;
	free(env);
	return (value);
}

void	run_unset(char *cmd, t_minishell *shell, bool parent)
{
	t_env	*iter;
	t_env	*remove;

	(void) parent;
	remove = shell->envs;
	iter = NULL;
	while (remove)
	{
		if (ft_strncmp(cmd, remove->name, ft_strlen(remove->name) + 1) == 0)
		{
			if (iter)
				iter->next = remove->next;
			else
				shell->envs = remove->next;
			free (remove->name);
			free (remove->value);
			free (remove);
			break ;
		}
		iter = remove;
		remove = remove->next;
	}
}
