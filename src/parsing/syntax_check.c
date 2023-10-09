/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 22:20:23 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/09 20:55:22 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

bool	check_empty_pipes(char *input)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	while (input && input[i])
	{
		if (flag && input[i] == '|')
		{
			printf("syntax error: pipes\n");
			g_exitcode = 258;
			return (false);
		}
		else if (input[i] == '|')
			flag = true;
		else if (!ft_isspace(input[i]))
			flag = false;
		i++;
	}
	return (true);
}

bool	is_syntax_valid(char *input)
{
	size_t	i;
	t_flag	flag;

	i = 0;
	flag.quote = true;
	flag.redir = true;
	flag.pipe = true;
	if (!check_empty_pipes(input))
		return (false);
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
		g_exitcode = 258;
		return (false);
	}
	return (true);
}
