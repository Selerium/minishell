/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:44:49 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/08 19:33:43 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	a replacement to the system pwd.
*
*	uses getcwd() to return current working directory
*/
int	run_pwd(char **cmd)
{
	char	*str;

	if (cmd[1])
		return (printf("pwd: wrong number of arguments\n"));
	str = getcwd(NULL, 0);
	if (!str)
		return (printf("Folder deleted\n"));
	printf("%s\n", str);
	wrap_free (str);
	g_exitcode = 0;
	return (0);
}
