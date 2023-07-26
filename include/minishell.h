/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 17:12:59 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<sys/stat.h>
# include<sys/resource.h>
# include<signal.h>
# include<dirent.h>
# include<string.h>
# include<stdbool.h>

# include"../libft/libft.h"
# include"structs.h"
# include"cmd_struct.h"

//built-ins:
int		pwd(t_env *envs);
t_env	*new_export(t_env *var, t_env *env);
// int cd(char *input);

//environment variables:
t_env	*make_lst(char *name, char *value);
t_env	*fill_vars(char **env);

#endif