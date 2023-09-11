/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:30:40 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/09 17:13:50 by jadithya         ###   ########.fr       */
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

void	run_unset(char *cmd, t_minishell *shell)
{
	t_env	*temp;

	temp = shell->envs;
	if (ft_strncmp(temp->name, cmd, ft_strlen(temp->name)) == 0)
	{
		shell->envs = free_single_env(temp);
		return ;
	}
	while (temp->next)
	{
		if (ft_strncmp(temp->next->name, cmd, ft_strlen(temp->next->name)) == 0)
		{
			temp->next = free_single_env(temp->next);
			return ;
		}
		temp = temp->next;
	}
}
