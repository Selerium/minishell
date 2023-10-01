/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:46:27 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/01 22:01:33 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

size_t	strlen_2d(char **arr)
{
	size_t	s;

	s = 0;
	if (!arr)
		return (s);
	while (arr[s])
		s++;
	return (s);
}

void	**realloc_2d(void **og, size_t new_size)
{
	size_t	i;
	void	**new;

	i = 0;
	new = (void **)ft_calloc(sizeof(void *), (new_size + 1));
	while (og && og[i])
	{
		new[i] = og[i];
		i++;
	}
	new[new_size] = NULL;
	free(og);
	return (new);
}

t_redir	*realloc_xd(t_redir *og, size_t new_size)
{
	size_t	i;
	t_redir	*new;

	i = 0;
	new = (t_redir *)ft_calloc(sizeof(t_redir), (new_size + 1));
	while (og && og[i])
	{
		new[i] = og[i];
		i++;
	}
	new[new_size] = '\0';
	free(og);
	return (new);
}

bool	check_space(int c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (true);
	return (false);
}
