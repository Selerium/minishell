/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/05 11:43:30 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// split input by the pipes

// and store in the linked list

// tokenize each "word" in the string

bool	condition(char c, int quote)
{
	if (check_space(c) && (quote == 0))
		return (true);
	else if ((c == '>' || c == '<') && (quote == 0))
		return (true);
	return (false);
}

char	**get_args(char **var, char *input, size_t *j, size_t *size)
{
	size_t	len;
	char	**new;
	int		quote;
	bool	end_arg;

	len = 0;
	quote = 0;
	end_arg = false;
	new = (char **)realloc_2d((void **)var, *size + 1);
	while ((input[*j] && check_space(input[*j]))
		|| (input[*j] == '>' || input[*j] == '<'))
		(*j)++;
	while (input[*j] && !end_arg)
	{
		quote = get_quote_type(quote, input[*j]);
		if (condition(input[*j], quote))
			end_arg = true;
		else
		{
			len++;
			(*j)++;
		}
	}
	(*size)++;
	new[(*size) - 1] = ft_substr(input, (*j) - len, len);
	(*j)--;
	return (new);
}

void	fill_struct_mini(char *split, t_chunk *chunk)
{
	size_t	j;

	j = 0;
	while (split[j])
	{
		if (split[j] == '>')
		{
			chunk->redir_out_type = get_redir_type(chunk->redir_out_type,
					split, &j, chunk->redir_out_count);
			chunk->redir_out = get_args(chunk->redir_out,
					split, &j, &chunk->redir_out_count);
		}
		else if (split[j] == '<')
		{
			chunk->redir_in_type = get_redir_type(chunk->redir_in_type, split,
					&j, chunk->redir_in_count);
			chunk->redir_in = get_args(chunk->redir_in, split,
					&j, &chunk->redir_in_count);
		}
		else if (split[j] != '>' && split[j] != '>' && !check_space(split[j]))
			chunk->cmd = get_args(chunk->cmd, split, &j, &chunk->cmd_count);
		if (split[j])
			j++;
	}
}

void	set_next_node(t_minishell *shell, t_chunk *new, t_chunk **head)
{
	if (shell->cmds == NULL)
	{
		*head = new;
		shell->cmds = new;
	}
	else
	{
		shell->cmds->next = new;
		shell->cmds = shell->cmds->next;
	}
}

void	fill_struct(t_minishell *shell)
{
	t_chunk	*new;
	t_chunk	*head;
	char	**split;
	size_t	i;

	i = 0;
	split = ms_split(shell->str, '|', 0, 0);
	shell->cmds = NULL;
	head = shell->cmds;
	while (split[i])
	{
		new = init_chunk();
		fill_struct_mini(split[i], new);
		expand_tokens(new->cmd, *shell);
		expand_tokens(new->redir_in, *shell);
		expand_tokens(new->redir_out, *shell);
		set_next_node(shell, new, &head);
		free (split[i]);
		i++;
	}
	free(split);
	free(shell->str);
	shell->cmds = head;
}
