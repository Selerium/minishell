/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/01 13:59:38 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	finds cd keyword and gets required file path from the next string
*/
void	run_cd(char **input, bool parent)
{
	int	i;

	(void) parent;
	i = 0;
	while (input[i] != NULL && ft_strncmp(input[i], "cd", 2) != 0)
		i++;
	if (input[i])
	{
		if (input[i + 1] == NULL || chdir(input[i + 1]) != 0)
			perror("cd Error");
	}
}
