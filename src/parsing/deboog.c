/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deboog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:46:54 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/13 19:51:31 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void    deboog(t_chunk *chunk)
{
    size_t  i;
    size_t  j;
    
    while (chunk)
    {
        i = 0;
        j = 0;
        while (chunk->redir_out && chunk->redir_out[i] != NULL)
        {
            printf("redir_out[%ld] = %s\n", i, chunk->redir_out[i]);
            i++;
        }
        while (chunk->redir_in && chunk->redir_in[j] != NULL)
        {
            printf("redir_in[%ld] = %s\n", i, chunk->redir_in[j]);
            j++;
        }
        chunk = chunk->next;
    }
}