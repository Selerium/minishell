/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/13 15:14:14 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_exp(t_chunk *node, char **cmd_array)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (cmd_array[i])
	{
		while (cmd_array[i][j] != '$')
			j++;
		start = j;
		while (cmd_array[i][j] != j)
		
		
	}
}



/*go through each node in linked list*/
/*go through each array
	if string contains '$'
	check if its inside quotes,
	if DOUBLE
		return env value
	if SINGLE
		return literal string
	then check if env var exists
	if exists
		replace with env value
	if not
		return empty string
	*/