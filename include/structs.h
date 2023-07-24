/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:40:22 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/24 19:03:24 by jebucoy          ###   ########.fr       */
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
	char	*cmd;
	char	**args;
}				t_cmd;


#endif