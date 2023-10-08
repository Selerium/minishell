/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:40:20 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/08 14:17:57 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_assignment(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			break ;
		i++;
	}
	if (!cmd[i])
		return (false);
	if (i > 0 && cmd[i + 1])
		return (true);
	return (false);
}

void	run_env(t_minishell *shell, bool parent)
{
	if (!shell->cmds->cmd[1])
		print_envs(shell->envs, parent);
	else if (check_assignment(shell->cmds->cmd[1]))
		run_export(shell->cmds->cmd, shell, parent);
	if (!parent)
		free_envs(shell->envs);
}
