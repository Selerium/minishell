/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/13 18:34:49 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// split input by the pipes

// and store in the linked list

// tokenize each "word" in the string

bool    check_space(int c)
{
    if ((c >= 9 && c <= 13) || (c == 32))
        return (true);
    return (false);
}

char    **realloc_2d(char **og, size_t new_size)
{
    size_t  i;
    char    **new;

    i = 0;
    new = (char **)malloc(sizeof(char *) * (new_size + 1));
    while(og && og[i])
    {
        new[i] = og[i];
        i++;
    }
    new[new_size - 1] = NULL;
    free(og);
    return (new);
}

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

size_t  strlen_2d(char **arr)
{
    size_t  s;

    s = 0;
    if (!arr)
        return (s);
    while (arr[s])
        s++;
    return (s);
}

void    get_file_name(char **out, char *input, size_t *j, char r)
{
    size_t  len;
    size_t  len_2d;

    (void)r;
    len = 0;
    len_2d = strlen_2d(out);
    out = realloc_2d(out, len_2d + 1);
    (*j)++;
    while (input[*j] && check_space(input[*j]))
        (*j)++;
    while (input[(*j)] && !check_space(input[(*j)]))
    {
        len++;
        (*j)++;
    }
    if ( len_2d == 0 )
        out[0] = ft_substr(input, (*j) - len, len);
    else
        out[len_2d] = ft_substr(input, (*j) - len, len);
    printf("%s\n", out[len_2d]);
    printf("%s, j = %ld, len = %ld\n", input, (*j) - len, len);
}




void    set_args(t_minishell *shell)
{
    t_chunk *chunk;
    char    **split;
    size_t  i;
    size_t  j;
    // size_t  io;
    
    chunk = (t_chunk *)malloc(sizeof(t_chunk));
    i = 0;
    j = 0;
    chunk->redir_in = NULL;
    chunk->redir_out = NULL;
    chunk->cmd = NULL;
    split = ft_split(shell->str, '|');
    // io = 0;
    while (split[i])
    {
        j = 0;
        while (split[i][j])
        {
            if (split[i][j] == '>')
                get_file_name(chunk->redir_out, split[i], &j, '>');
            else if (split[i][j] == '<')
                 get_file_name(chunk->redir_in, split[i], &j, '<');
            else
                printf("get_args()\n");
            if (split[i][j])
                j++;
                // get_args();
        }
        i++;
    }
    // shell->cmds = chunk;
}