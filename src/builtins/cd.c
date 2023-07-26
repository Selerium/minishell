/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/07/26 18:39:41 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int ms_cd(char **input)
{
//    ** find keyword cd
//    ** look for the string next to cd
	int i;

	i = 0;
	while (input[i] != NULL && ft_strncmp(input[i], "cd", 2) != 0)	
		i++;
	if (input[i])
	{
		if (input[i + 1] != NULL && chdir(input[i + 1]) == 0)
			printf("%s\n", getcwd(NULL, 0));
		else	
		{
			// errno = 20;
			perror("Error");
		}
	}
	return (0);
}