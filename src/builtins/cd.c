/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:39:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/07/24 18:57:15 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int cd(char *input)
{
//    ** find keyword cd
//    ** look for the string next to cd
	void(env);
	
	if (chdir(av[1]) != 0)
		perror("Error");
	return (0);
}