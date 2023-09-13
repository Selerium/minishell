/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/13 20:12:45 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;

	i = 0;
	while (input[i] != '$')
		i++;
	start = i + 1;
	while (isalnum(input[i]) || input[i] == '_')
	;
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