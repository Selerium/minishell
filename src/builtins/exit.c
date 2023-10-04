/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:14:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 21:53:10 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	single_exit(t_chunk *cmds, t_env *envs, char *cmd)
{
	free_cmd(cmds);
	free_envs(envs);
	run_exit(cmd);
}

void	run_exit(char *num)
{
	int	n;

	n = ft_atoi(num);
	free(num);
	if (n > 255)
		run_exit(ft_itoa(n - 256, '0', 0));
	printf("Exiting minishell. Thanks :\")");
	exit(n);
}
