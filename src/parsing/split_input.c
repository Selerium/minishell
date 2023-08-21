/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:49:07 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/21 13:25:22 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

// split input by the pipes

// and store in the linked list

// tokenize each "word" in the string

enum e_redir    *get_redir_type(enum e_redir *redir, char *input, size_t *j, size_t size)
{
    enum e_redir    *new;
    char    r;

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

char    **get_file_name(char **out, char *input, size_t *j, size_t *size)
{
    size_t  len;
    // size_t  len_2d;
    char    **new;

    len = 0;
    // len_2d = strlen_2d(out);
    new = (char **)realloc_2d((void **)out, *size + 1);
    while ((input[*j] && check_space(input[*j]))
        || (input[*j] == '>' || input[*j] == '<'))
        (*j)++;
    while (input[(*j)] && !check_space(input[(*j)])
        && (input[*j] != '>' && input[*j] != '<'))
    {
        len++;
        (*j)++;
    }
    (*size)++;
    new[(*size) - 1] = ft_substr(input, (*j) - len, len);
    (*j)--;
    return (new);
}


char    **get_args(t_chunk *chunk, char *input, size_t *j, size_t *size)
{
    char    **new;
    size_t  len;
    // size_t  i;

    len = 0;
    new = (char **)realloc_2d((void **)chunk->cmd, *size + 1);
    while (input[*j] && check_space(input[*j])
        && (input[*j] == '>' || input[*j] == '<'))
        (*j)++;
    while (input[(*j)] && !check_space(input[(*j)]))
    {
        len++;
        (*j)++;
    }
    (*size)++;
    new[(*size) - 1] = ft_substr(input, (*j) - len, len);
    return (new);
}

void    fill_struct(t_minishell *shell)
{
    t_chunk *chunk;
    t_chunk *head;
    char    **split;
    size_t  i;
    size_t  j;
    size_t  in;
    size_t  out;
    
    chunk = (t_chunk *)malloc(sizeof(t_chunk));
    i = 0;
    j = 0;
    in = 0;
    out = 0;
    split = my_split(shell->str, '|');
    // print_split(split);
    head = chunk;
    while (split[i])
    {
        j = 0;
        chunk->redir_in = NULL;
        chunk->redir_out = NULL;
        chunk->cmd = NULL;
        chunk->next = NULL;
        chunk->redir_in_type = NULL;
        chunk->redir_out_type = NULL;
        chunk->redir_in_count = 0;
        chunk->redir_out_count = 0;
        chunk->cmd_count = 0;
        while (split[i][j])
        {
            if (split[i][j] == '>')
            {
                chunk->redir_out_type = get_redir_type(chunk->redir_out_type, split[i], &j, chunk->redir_out_count); 
                chunk->redir_out = get_file_name(chunk->redir_out, split[i], &j, &chunk->redir_out_count);
                out++;
            }
            else if (split[i][j] == '<')
            {
                chunk->redir_in_type = get_redir_type(chunk->redir_in_type, split[i], &j, chunk->redir_in_count); 
                chunk->redir_in = get_file_name(chunk->redir_in, split[i], &j, &chunk->redir_in_count);
                in++;
            }
            else if (split[i][j] != '>' && split[i][j] != '>' && !check_space(split[i][j]))
                chunk->cmd = get_args(chunk, split[i], &j, &chunk->cmd_count);
            j++;
        }
        i++;
        if (split[i] != NULL)
        {
            chunk->next = (t_chunk *)malloc(sizeof(t_chunk));
            chunk = chunk->next;
            chunk->next = NULL;
        }
    }
    chunk = head;
    deboog(chunk);
    // shell->cmds = chunk;
}