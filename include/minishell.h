/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:58:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 15:20:39 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WRITE 1
# define READ 0
# define LEFT 0
# define RIGHT 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>

# include "../libft/libft.h"
# include "structs.h"
# include "exit_codes.h"

# define DOUBLE 34
# define SINGLE 39

extern int	g_exitcode;

void	our_readline(t_minishell *shell);
void	print_welcome(int ac, char **av);
int		run_single_cmd_mini(t_chunk *cmds, t_minishell *shell, char *cmd);
int		run_single_cmd(t_chunk *cmds, t_minishell *shell);

//environment variables:
t_env	*get_env(char *name, t_minishell shell);
t_env	*add_env(char *str, t_minishell *shell);
t_env	*create_envs(char **env, t_minishell *shell);
void	print_envs(t_env *envs, bool is_env);
void	free_envs(t_env *envs);

//signal handlers:
void	sigint_handler(int n);
void	set_handlers(t_minishell *shell);
void	set_child_handlers(t_minishell *shell);
//doesnt't belong there, just kept for norm
bool	envcondition(char *a, char *b);
void	special_free(t_minishell *shell);

//run shell with set of commands:
void	set_num_chunks(t_chunk *cmd, t_env *env, t_minishell *shell);
int		**create_fds(t_minishell *shell);
t_chunk	*free_iter(t_chunk *cmd);
void	close_run(t_minishell *shell);
void	run_cmd(t_chunk *cmds, t_minishell *shell);

//find command path:
char	*ft_wrapjoin(char *str1, char *str2);
char	*ft_findpath(t_env *paths, char *cmd);
char	*ft_findcmd(char *cmd, t_env *env);

//execute separate commands:
void	dup_redirects(t_chunk *cmd);
void	make_envs_array(t_env *envs, char **list);
void	execute_cmd(t_chunk *cmd, t_minishell *shell, int i);
void	wrap_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell);
void	ft_execve(char *cmdpath, char **cmd, char **envs, t_minishell *shell);

//running minishell within minishell:
void	run_minishell(char *cmdpath, char **cmd, char **envs,
			t_minishell shell);

//cleanup:
void	close_pipes(t_minishell *shell);
void	close_unneededs(t_chunk *cmd, t_minishell *shell, int i, bool parent);
void	check_to_free_envs(t_chunk *cmd, char **envs, t_minishell *shell);
void	print_exit(char **envs, t_minishell *shell, char *error, int errnum);
void	close_fds(t_minishell *shell, int *fds, int n);

//redirections:
int		set_redir_counts(char **list);
void	heredoc_sig(int x);
void	heredoc(int fd, char *delimiter, t_minishell shell);
bool	exit_outfiles(t_minishell *shell, t_chunk *cmd, int i);
bool	open_outfiles(t_chunk *cmd, t_minishell *shell);
bool	exit_infiles(t_minishell *shell, t_chunk *cmd, int i, char *msg);
bool	open_infiles(t_chunk *cmd, t_minishell *shell);
void	open_heredoc(t_chunk *cmd, t_minishell *shell, int i);
bool	set_redirects(t_chunk *cmd, t_minishell *shell);

//freeing:
void	wrap_free(void *item);
void	free_cmd(t_chunk *cmd);
void	free_redirs(t_chunk *cmd);
void	free_fds(int **fds, int n);
void	free_shell(t_minishell *shell);

//handling flags:
void	handle_redirection(char *input, t_flag *flag, size_t *i, char n);
void	handle_quotes(char *input, t_flag *flag, size_t *i, char n);
void	handle_pipes(char *input, t_flag *flag, size_t *i);

//getting redirs:
t_redir	*get_redir_type(t_redir *redir, char *input, size_t *j, size_t size);

//splitting input:
bool	condition(char c, int quote);
char	**get_args(char **var, char *i, size_t *j, size_t *size);
void	fill_struct_mini(char *split, t_chunk *chunk);
void	set_next_node(t_minishell *shell, t_chunk *nnew, t_chunk **head);
void	fill_struct(t_minishell *shell);

//pre-parsing:
bool	print_error(t_flag flag);
bool	check_empty_pipes(char *input);
bool	is_syntax_valid(char *input);

// utils:
size_t	strlen_2d(char **arr);
void	**realloc_2d(void **og, size_t new_size);
t_redir	*realloc_xd(t_redir *og, size_t new_size);
bool	check_space(int c);
t_chunk	*init_chunk(void);

// using ft_split from jensen's libft:
char	**ms_split(char *s, char c, size_t i, size_t j);

// expansion
char	*get_env_name(char *input);
char	*replace_env(char *input, size_t *idx, char *var_name, char *env);
char	*check_val_conds(char *val, char *name, t_minishell shell);
char	*expand_env(char *input, t_minishell shell, int qflag);
void	expand_tokens(char **args, t_minishell shell, int type);

// quotes
int		get_quote_type(int qflag, char q);
char	*eliminate_quotes(char *input, size_t *idx);
char	*trim_quotes(char *input);

//built-ins:
void	run_cd(char **input, bool parent);

void	run_echo(char **cmd);

int		run_pwd(char **cmd);

bool	check_assignment(char *cmd);
void	run_env(t_minishell *shell, bool parent);

t_env	*free_single_env(t_env *env);
void	wrap_unset(char **cmd, t_minishell *shell, bool parent);
void	run_unset(char *cmd, t_minishell *shell, bool parent);

bool	check_export_cmd(char *cmd);
void	wrap_export(char **cmd, t_minishell *shell);
void	env_exists_mini(t_env *iter_env, t_env *hold);
bool	env_exists(char *cmd, t_minishell *shell, bool is_env);
void	run_export(char *cmd, t_minishell *shell, bool is_env);

void	free_envs_exit(t_env *envs, char *cmd, char *num, char *path);
int		single_exit(t_chunk *cmds, t_env *envs, char *cmd);
void	special_exit(t_minishell *shell, char *num, char *path);
void	wrap_exit(char **cmd, t_minishell *shell, char *path);
void	run_exit(char *num, int i);

#endif