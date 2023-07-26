/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:40:22 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 17:10:15 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct s_cmd {
	char			*cmd;
	char			**args;
	char			*infile;
	char			*outfile;
	struct s_cmd	*next;
}				t_cmd;


#endif