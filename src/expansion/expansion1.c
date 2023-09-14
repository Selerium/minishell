/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/14 16:02:46 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;
	size_t	count;
	char 	*env_name;

	i = 0;
	count = 0;
	while (input[i] != '$')
		i++;
	start = i + 1;
	while (isalnum(input[i]) || input[i] == '_')
	{
		i++;
		count++;
	}
	env_name = ft_substr(input, start, i);
	return (env_name);
}

void	expand_env(char *input, t_minishell shell)
{
	char	*name;

	name = get_env_name(input);
	get_env(name, shell);
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