/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:40:22 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 17:27:58 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
enum e_redir
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
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
	char			**args;
	char			**redir_in;
	enum e_redir	*redir_in_type;
	char			**redir_out;
	enum e_redir	*redir_out_type;
	struct s_chunk	*next;
}			t_chunk;

#endif