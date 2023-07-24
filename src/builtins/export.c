/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:31:10 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/22 14:24:25 by jadithya         ###   ########.fr       */
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

int	new_export(char *name, char *value, char **env)
{
	int	i;
	int	size;
	int	flag;

	i = -1;
	size = ft_strlen(name);
	flag = 1;
	while (env[++i])
	{
		flag = (ft_strncmp(env[i], name, size));
		if (flag <= 0)
			break ;
	}
	if (flag != 0)
		i--;
	env[i] = ft_strdup(name);
	return (0);
}
