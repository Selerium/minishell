/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/13 19:47:32 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// split input by the pipes

// and store in the linked list

// tokenize each "word" in the string

enum e_redir    get_redir_type(char *input, size_t *j, char r)
{
    if (input[*j])
        (*j)++;
    if (check_space(input[(*j)]))
    {
        if (r == '>')
            return (REDIR_OUT);
        else if (r == '<')
            return (REDIR_IN);
    }
    if (input[(*j)] == '>')
        return (APPEND);
    if (input[(*j)] == '<')
        return (HEREDOC);
    return (0);
}



char    **get_file_name(char **out, char *input, size_t *j, char r)
{
    size_t  len;
    size_t  len_2d;
    char    **new;

    (void)r;
    len = 0;
    len_2d = strlen_2d(out);
    printf("len2d = %ld\n", len_2d);
    new = realloc_2d(out, len_2d + 1);
    (*j)++;
    while (input[*j] && check_space(input[*j]))
        (*j)++;
    while (input[(*j)] && !check_space(input[(*j)]))
    {
        len++;
        (*j)++;
    }
    len_2d = strlen_2d(new);
    new[len_2d - 1] = ft_substr(input, (*j) - len, len);
    return (new);
}

void    set_args(t_minishell *shell)
{
    t_chunk *chunk;
    char    **split;
    size_t  i;
    size_t  j;
    
    chunk = (t_chunk *)malloc(sizeof(t_chunk));
    i = 0;
    j = 0;
    chunk->redir_in = NULL;
    chunk->redir_out = NULL;
    chunk->cmd = NULL;
    chunk->next = NULL;
    split = ft_split(shell->str, '|');
    while (split[i])
    {
        j = 0;
        while (split[i][j])
        {
            if (split[i][j] == '>')
                chunk->redir_out = get_file_name(chunk->redir_out, split[i], &j, '>');
            else if (split[i][j] == '<')
                chunk->redir_in = get_file_name(chunk->redir_in, split[i], &j, '<');
            else
                printf("get_args()\n");
            if (split[i][j])
                j++;
                // get_args();
        }
        i++;
    }
    deboog(chunk);
    // shell->cmds = chunk;
}