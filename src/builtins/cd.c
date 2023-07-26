/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/07/26 18:18:51 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	finds cd keyword and gets required file path from the next string
*/
int	ms_cd(char **input)
{
	int	i;

	i = 0;
	while (input[i] != NULL && ft_strncmp(input[i], "cd", 2) != 0)
		i++;
	if (input[i])
	{
		if (input[i + 1] != NULL && chdir(input[i + 1]) == 0)
			printf("%s\n", getcwd(NULL, 0));
		else
		{
			errno = 20;
			perror("Error");
		}
	}
	return (0);
}
