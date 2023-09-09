/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/05 18:17:30 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WRITE 1
# define READ 0
# define LEFT 0
# define RIGHT 1

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

# define DOUBLE '\"'
# define SINGLE '\''

//built-ins:
int		pwd(void);
t_env	*new_export(t_env *var, t_env *env);
int		ms_cd(char **input);

//environment variables:
t_env	*add_env(char *str);
t_env	*create_envs(char **env);
void	print_envs(t_env *envs);
void	free_envs(t_env *envs);

//signal handlers:
void	sigint_handler(int n);
void	set_handlers(t_minishell *shell);
void	set_child_handlers(t_minishell *shell);

//pre-parsing 
bool	is_syntax_valid(char *input);
void	handle_redirection(char *input, t_flag *flag, size_t *i, char n);
void	handle_quotes(char *input, t_flag *flag, size_t *i, char n);
void	handle_pipes(char *input, t_flag *flag, size_t *i);

//tokenizing the string
void	fill_struct(t_minishell *shell);

int		is_quotes_closed(int qflag, char q);

// debug
void	deboog(t_chunk *chunk);
void	print_split(char **str);

// utils
size_t	strlen_2d(char **arr);
void	**realloc_2d(void **og, size_t new_size);
enum e_redir	*realloc_xd(enum e_redir *og, size_t new_size);
bool	check_space(int c);
char	**ms_split(char *s, char c); // using ft_split from jensen's libft 

//execution:
void	free_shell(t_minishell *shell);
void	run_cmd(t_chunk *cmds, t_minishell *shell);
void	set_num_chunks(t_chunk *cmd, t_minishell *shell);

#endif