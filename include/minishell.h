/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/04 14:55:36 by jebucoy          ###   ########.fr       */
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

void	our_readline(t_minishell *shell);
void	print_welcome(int ac, char **av);
int		run_single_cmd(t_chunk *cmds, t_minishell *shell);

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

//run shell with set of commands:
void	set_num_chunks(t_chunk *cmd, t_env *env, t_minishell *shell);
int		**create_fds(t_minishell *shell);
t_chunk	*free_iter(t_chunk *cmd);
void	run_cmd(t_chunk *cmds, t_minishell *shell);

//find command path:
char	*ft_wrapjoin(char *str1, char *str2);
char	*ft_findpath(t_env *paths, char *cmd);
char	*ft_findcmd(char *cmd, t_env *env);

//execute separate commands:
void	dup_redirects(t_chunk *cmd);
void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i);
void	run_minishell(char *cmdpath, char **cmd, char **envs,
			t_minishell shell);
void	wrap_execve(char *cmdpath, char **cmd, char **envs);
void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell);

//cleanup:
void	close_pipes(t_minishell *shell);
void	close_unneededs(t_chunk *cmd, t_minishell *shell, int i);
void	print_exit(char **envs, t_minishell *shell, char *error);
void	check_to_free_envs(t_chunk *cmd, char **envs, t_minishell *shell);
void	close_fds(t_minishell *shell, int *fds, int n);

//redirections:
int		set_redir_counts(char **list);
void	heredoc(int fd, char *delimiter);
void	open_outfiles(t_chunk *cmd, t_minishell *shell);
void	open_infiles(t_chunk *cmd, t_minishell *shell);
void	set_redirects(t_chunk *cmd, t_minishell *shell);

//freeing:
void	free_cmd(t_chunk *cmd);
void	free_redirs(t_chunk *cmd);
void	free_fds(int **fds, int n);
void	free_shell(t_minishell *shell);

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
char	*eliminate_quotes(char *input, size_t *idx);

// test con:
//  ls < oat > outals < oat > outaaa | pwd < outie < outa > also
// > hey | echo > hey > also hiiii thereeee < oat

#endif