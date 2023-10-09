/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:02:22 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 17:53:18 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redir	*get_redir_type(t_redir *redir, char *input, size_t *j, size_t size)
{
	t_redir	*new;
	char	r;

	r = input[*j];
	new = realloc_xd(redir, size + 1);
	if (input[*j])
		(*j)++;
	if (input[(*j)] == '>')
		new[size] = APPEND;
	else if (input[(*j)] == '<')
		new[size] = HEREDOC;
	else if (r == '>')
		new[size] = REDIR_OUT;
	else if (r == '<')
		new[size] = REDIR_IN;
	return (new);
}
