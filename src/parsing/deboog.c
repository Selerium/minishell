/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deboog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:46:54 by jebucoy           #+#    #+#             */
/*   Updated: 2023/08/12 18:59:12 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void    deboog(t_chunk *chunk)
{
    size_t  i;
    
    while (chunk)
    {
        i = 0;
        while (chunk->redir_out[i] != NULL)
        {
            printf("chunk[%ld] = %s\n", i, chunk->redir_out[i]);
            i++;
        }
        chunk = chunk->next;
    }
}