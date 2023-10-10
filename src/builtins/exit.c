/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:14:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/10 18:05:23 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envs_exit(t_env *envs, char *cmd, char *num, char *path)
{
	free_envs(envs);
	wrap_free(cmd);
	wrap_free(path);
	run_exit(num);
}

int	single_exit(t_chunk *cmds, t_env *envs, char *cmd)
{
	bool	juju;
	char	*num;
	int		i;

	i = 0;
	juju = false;
	if (cmds->cmd[1] && cmds->cmd[2])
		juju = true;
	free_cmd(cmds);
	if (juju)
	{
		printf("exit: too many arguments\n");
		num = ft_strdup("1");
		while (cmd[i])
			if (!ft_isdigit(cmd[i++]))
				free_envs_exit(envs, cmd, num, NULL);
		wrap_free(cmd);
		wrap_free(num);
		return (1);
	}
	free_envs(envs);
	run_exit(cmd);
	return (1);
}

void	special_exit(t_minishell *shell, char *num, char *path)
{
	wrap_free(path);
	free_cmd(shell->cmds);
	run_exit(num);
}

void	wrap_exit(char **cmd, t_minishell *shell, char *path)
{
	bool	juju;
	char	*num;
	int		i;

	i = 0;
	juju = false;
	if (cmd[1] && cmd[2])
		juju = true;
	if (juju)
	{
		printf("exit: too many arguments\n");
		num = ft_strdup("1");
		while (cmd[1][i])
			if (!ft_isdigit(cmd[1][i++]))
				special_exit(shell, num, path);
		wrap_free(num);
		return ;
	}
	special_exit(shell, ft_strdup(cmd[1]), path);
}

void	run_exit(char *num)
{
	int	i;
	int	n;

	if (!num)
	{
		printf("Exiting minishell. Thanks :\")");
		exit(0);
	}
	i = 0;
	while (num[0] != '+' && num[i])
	{
		if (!ft_isdigit(num[i++]))
		{
			printf("exit: numeric argument required\n");
			wrap_free(num);
			exit(255);
		}
	}
	n = ft_atoi(num);
	wrap_free(num);
	if (n > 255)
		run_exit(ft_itoa(n - 256, '0', 0));
	printf("Exiting minishell. Thanks :\")");
	exit(n);
}
