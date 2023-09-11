/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/11 17:06:43 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	finds cd keyword and gets required file path from the next string
*/
int	run_cd(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL && ft_strncmp(input[i], "cd", 2) != 0)
		i++;
	if (input[i])
	{
		if (input[i + 1] != NULL)
			printf("%s\n", getcwd(NULL, 0));
		else
			perror("Error");
	}
	exit (0);
}

