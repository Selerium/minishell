/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/06 12:25:29 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	finds cd keyword and gets required file path from the next string
*/
void	run_cd(char **input, bool parent)
{
	(void) parent;
	if (input[1])
	{
		if (chdir(input[1]) != 0)
			perror("cd: cannot change directory");
	}
	else
		chdir("/");
}
