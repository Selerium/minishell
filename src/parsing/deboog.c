/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deboog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:46:54 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/14 20:27:19 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void    deboog(t_chunk *chunk)
{
    size_t  i;
    size_t  j;
    size_t  r_i;
    size_t  r_o;
    size_t  cmd;
    
    r_i = 0;
    r_o = 0;
    cmd = 0;
    while (chunk)
    {
        i = 0;
        j = 0;
        while ((chunk->redir_out && chunk->redir_out[i] != NULL)
            || (chunk->redir_out_type && chunk->redir_out_type[r_o]))
        {
            printf("redir_out[%ld] = %s\n", i, chunk->redir_out[i]);
            printf("redir_out_type[%ld] = %d\n", r_o, chunk->redir_out_type[r_o]);
            i++;
            r_o++;
        }
        printf("\n");
        while ((chunk->redir_in && chunk->redir_in[j] != NULL)
            || (chunk->redir_in_type && chunk->redir_in_type[r_i]))
        {
            printf("redir_in[%ld] = %s\n", j, chunk->redir_in[j]);
            printf("redir_in_type[%ld] = %d\n", r_i, chunk->redir_in_type[r_i]);
            r_i++;
            j++;
        }
        while (chunk->cmd && chunk->cmd[cmd])
        {
            printf("cmd[%ld] = %s\n", cmd, chunk->cmd[cmd]);
            cmd++;
        }
        printf("\n");
        chunk = chunk->next;
    }
}