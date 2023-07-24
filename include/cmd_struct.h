/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:05:29 by jebucoy           #+#    #+#             */
/*   Updated: 2023/07/24 19:06:03 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_STRUCT_H
# define CMD_STRUCT_H

/**
               |-> t_minishell  minishell->cmd
               |
|- -------------------------------------------------|
 echo    hi     >     test.txt   |   cat       -e
 |____________________________|     |_____________|
  |_______|     |      |_____|       |__|  |   |_|
   |     |      |         |           |    |    |
   |     v      |         |        ___|    |    |_-> args[1]
   |    args[1] |         |       |        |
   |            |         |       v        |
   v            |         |    args[0]     |
 args[0]        |         |                v
                |         v            cmd->next;
                |    redir_out[0]
                |   redir_out_type[0] = REDIR_OUT
                v
            t_cmd *cmd;
**/

typedef struct	s_flag
{
	bool	quote;
	bool	pipe;
	bool	redir;
	bool	env_var;
}	t_flag;

typedef enum	e_def
{
	WORD,
	INPUT,
	OUTPUT,
	PIPE,
	ENV_VAR, 
	QUOTE,	
}	t_def;

enum e_redir
{
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
};

typedef struct s_chunk
{
    char                    **args; // cmd && args excluding the redirections
    char                    **redir_in; // redir in filename 
    enum e_redir            *redir_in_type;
    char                    **redir_out; // redir out filename 
    enum e_redir            *redir_out_type; 
    struct s_chunk            *next;
} t_chunk;

typedef struct s_minishell
{
    int     exit_code;
    t_cmd   *cmd;
} t_minishell;

#endif