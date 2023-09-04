/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/04 18:03:12 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// split input by the pipes

// and store in the linked list

// tokenize each "word" in the string

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
		quote = is_quotes_closed(quote, input[*j]);
		if (check_space(input[*j]) && (quote == 0))
			end_arg = true;
		else if ((input[*j] == '>' || input[*j] == '<') && (quote == 0))
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

t_chunk	*init_chunk(void)
{
	t_chunk	*chunk;

	chunk = (t_chunk *)malloc(sizeof(t_chunk));
	chunk->redir_in = NULL;
	chunk->redir_out = NULL;
	chunk->cmd = NULL;
	chunk->next = NULL;
	chunk->redir_in_type = NULL;
	chunk->redir_out_type = NULL;
	chunk->redir_in_count = 0;
	chunk->redir_out_count = 0;
	chunk->cmd_count = 0;
	return (chunk);
}

t_chunk	*fill_struct_mini(char *split)
{
	size_t	j;
	t_chunk	*chunk;

	j = 0;
	chunk = init_chunk();
	while (split[j])
	{
		if (split[j] == '>')
		{
			chunk->redir_out_type = get_redir_type(chunk->redir_out_type, split, &j, chunk->redir_out_count); 
			chunk->redir_out = get_args(chunk->redir_out, split, &j, &chunk->redir_out_count);
		}
		else if (split[j] == '<')
		{
			chunk->redir_in_type = get_redir_type(chunk->redir_in_type, split, &j, chunk->redir_in_count); 
			chunk->redir_in = get_args(chunk->redir_in, split, &j, &chunk->redir_in_count);
		}
		else if (split[j] != '>' && split[j] != '>' && !check_space(split[j]))
		{
			chunk->cmd = get_args(chunk->cmd, split, &j, &chunk->cmd_count);
			printf("cmd count: %ld\n", chunk->cmd_count);
		}
		if (split[j])
			j++;
	}
	return (chunk);
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
	split = my_split(shell->str, '|');
	shell->cmds = NULL;
	head = shell->cmds;
	while (split[i])
	{
		new = fill_struct_mini(split[i]);
		set_next_node(shell, new, &head);
		i++;
	}
	shell->cmds = head;
	deboog(shell->cmds);
}