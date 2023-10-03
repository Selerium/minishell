/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/03 20:15:19 by jebucoy          ###   ########.fr       */
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

void	free_shell(t_minishell *shell);

//environment variables:
t_env	*get_env(char *name, t_minishell shell);
t_env	*add_env(char *str);
t_env	*create_envs(char **env);
void	print_envs(t_env *envs, bool is_env);
void	free_envs(t_env *envs);
t_env	*get_env(char *name, t_minishell shell);

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

// debug
void	deboog(t_chunk *chunk);
void	print_split(char **str);

// utils
size_t	strlen_2d(char **arr);
void	**realloc_2d(void **og, size_t new_size);
t_redir	*realloc_xd(t_redir *og, size_t new_size);
bool	check_space(int c);
char	**ms_split(char *s, char c); 
// using ft_split from jensen's libft 

//find command path:
char	*ft_findcmd(char *cmd, t_env *env);

//execution:
void	dup_redirects(t_chunk *cmd);
void	close_pipes(t_minishell *shell);
void	set_num_chunks(t_chunk *cmd, t_env *env, t_minishell *shell);
int		**create_fds(t_minishell *shell);
void	run_cmd(t_chunk *cmds, t_minishell *shell);

//redirections:
int		set_redir_counts(char **list);
void	open_outfiles(t_chunk *cmd);
void	open_infiles(t_chunk *cmd);
void	set_redirects(t_chunk *cmd);
void	dup_redirects(t_chunk *cmd);

//execute separate commands:
void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i);
void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell);
void	close_pipes(t_minishell *shell);
void	close_unneededs(t_chunk *cmd, t_minishell *shell, int i);

//built-ins:
int		run_pwd(void);
void	run_env(t_minishell *shell, bool parent);
void	run_cd(char **input, bool parent);
void	run_export(char **cmd, t_minishell *shell, bool parent);
void	run_exit(char *num);
void	run_echo(char **cmd);
void	run_unset(char *cmd, t_minishell *shell, bool parent);

// expansion
char	*get_env_name(char *input);
char	*replace_env(char *input, size_t *idx, char *var_name, t_env *env);
char	*expand_env(char *input, t_minishell shell);
void	expand_tokens(char **args, t_minishell shell);

// quotes
int		get_quote_type(int qflag, char q);
char	*trim_quotes(char *input);
char	*eliminate_quotes(char *input, size_t *idx, int qflag, int old_qflag);
#endif