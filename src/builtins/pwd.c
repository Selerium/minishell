/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:44:49 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/21 15:55:43 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	a replacement to the system pwd.
*
*	uses getcwd() to return current working directory
*/
int	pwd(char **env)
{
	char	*str;

	(void) env;
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free (str);
	return (0);
}
