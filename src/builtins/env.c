/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 19:40:20 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/04 09:33:59 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_env(t_minishell *shell, bool parent)
{
	print_envs(shell->envs, parent);
	if (!parent)
		free_envs(shell->envs);
}
