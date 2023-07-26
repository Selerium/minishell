/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/26 19:59:46 by jadithya         ###   ########.fr       */
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
# include<errno.h>

# include"../libft/libft.h"
# include"structs.h"
# include"exit_codes.h"

//built-ins:
int		pwd(void);
t_env	*new_export(t_env *var, t_env *env);
int		ms_cd(char **input);

//environment variables:
t_env	*make_lst(char *name, char *value);
t_env	*fill_vars(char **env);

//signal handlers:
void	sigint_handler(int n);
void	set_handlers(void);
void	set_child_handlers(void);

//pre-parsing 
void    set_flags(char *input);
void    handle_redirection(char *input, t_flag *flag, size_t *i, char n);
void    handle_quotes(char *input, t_flag *flag, size_t *i, char n);
void    handle_pipes(char *input, t_flag *flag, size_t *i);

#endif