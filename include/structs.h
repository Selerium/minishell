/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:40:22 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/27 19:24:42 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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


typedef enum e_def
{
	WORD,
	INPUT,
	OUTPUT,
	PIPE,
	ENV_VAR,
	QUOTE,
}	t_def;

/**
*	enum for redirections
*	
*	>	values for the type of the redirection
*/
enum	e_redir_in
{
	REDIR_IN,
	HEREDOC
};

enum	e_redir_out
{
	REDIR_OUT,
	APPEND
};

/**
*	linked list to hold env vars.
*
*	>	name: the name of the variable
*	>	value: the value of the variable
*	>	next: the next var in list
*/
typedef struct s_env {
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

/**
*	linked list to hold each cmd and its params
*	
*	>	args: holds command and its args - pass in execve()
*	>	redir_in: list of infiles
*	>	redir_in_type: type of redirect
*	>	redir_out: list of outfiles
*	>	redir_out_type: type of redirect
*	>	next: the next command in list
*/
typedef struct s_chunk
{
	char				**args;
	char				**redir_in;
	enum e_redir_in		*redir_in_type;
	char				**redir_out;
	enum e_redir_out	*redir_out_type;
	struct s_chunk		*next;
}			t_chunk;

typedef struct s_flag
{
	bool	quote;
	bool	pipe;
	bool	redir;
	bool	env_var;
}	t_flag;

/**
*	the BIG struct.
*	
*	>	exit_code: exit code from a run command
*	>	str: string returned by readline()
*	>	cmds: linked list of cmds
*	>	envs: linked list of env vars
*/
typedef struct s_minishell
{
	int				exit_code;
	int				flag;
	char			*str;
	struct s_chunk	*cmds;
	struct s_env	*envs;
}			t_minishell;

#endif