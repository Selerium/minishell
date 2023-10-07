/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:44:49 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/07 16:45:56 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

/**
*	a replacement to the system pwd.
*
*	uses getcwd() to return current working directory
*/
int	run_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free (str);
	return (0);
}