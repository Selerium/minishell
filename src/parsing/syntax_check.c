/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:20:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/06 09:25:05 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// false means open quote found, true means closing quote found
bool	print_error(t_flag flag)
{
	if (flag.quote == false || flag.redir == false || flag.pipe == false)
	{
		if (flag.quote == false)
			printf("syntax error: unclosed quotes\n");
		else if (flag.redir == false)
			printf("syntax error: no file included for redirection\n");
		else if (flag.pipe == false)
			printf("syntax error: pipes\n");
		return (true);
	}
	return (false);
}

bool	is_syntax_valid(char *input)
{
	size_t	i;
	t_flag	flag;

	i = 0;
	flag.quote = true;
	flag.redir = true;
	flag.pipe = true;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			handle_quotes(input, &flag, &i, input[i]);
		if (input[i] == '>' || input[i] == '<')
			handle_redirection(input, &flag, &i, input[i]);
		if (input[i] == '|')
			handle_pipes(input, &flag, &i);
		i++;
	}
	if (print_error(flag) == true)
	{
		g_exitcode = 257;
		return (false);
	}
	return (true);
}
