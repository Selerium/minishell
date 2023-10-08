/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniminishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:44:05 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/08 14:43:12 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	run_minishell(char *cmdpath, char **cmd, char **envs, t_minishell shell)
{
	char	*num;
	int		val;
	int		i;

	i = 0;
	while (shell.envs)
	{
		if (ft_strncmp(shell.envs->name, "SHLVL", 6) == 0)
		{
			val = ft_atoi(shell.envs->value) + 1;
			num = ft_itoa(val, '0', 0);
			free(envs[i]);
			envs[i] = ft_strjoin("SHLVL=", num);
			printf("here %s\n", envs[i]);
			break ;
		}
		shell.envs = shell.envs->next;
		i++;
	}
	g_exitcode = 0;
	execve(cmdpath, cmd, envs);
	perror("Command not found");
	exit(127);
}
