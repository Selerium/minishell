/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:48:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/06 11:08:02 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <complex.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int	set_redir_counts(char **list)
{
	int	i;

	i = 0;
	if (list)
	{
		while (list[i])
			i++;
	}
	return (i);
}

void	heredoc(int fd, char *delimiter)
{
	char	*text;

	while (true)
	{
		printf("[%s] heredoc> ", delimiter);
		text = readline("");
		if (!text)
		{
			write(fd, "\n", 1);
			break ;
		}
		if (ft_strlen(text) == 0 || text[0] == '\n')
			printf("\n");
		if (ft_strncmp(text, delimiter, ft_strlen(text) + 1) == 0)
			break ;
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
	}
}

void	open_outfiles(t_chunk *cmd, t_minishell *shell)
{
	int	i;

	i = 0;
	if (cmd->redir_out)
	{
		while (cmd->redir_out[i])
		{
			if (access(cmd->redir_out[i], F_OK) == 0
				&& access(cmd->redir_out[i], W_OK) == -1)
			{
				close_pipes(shell);
				close_fds(shell, cmd->fds_out, i);
				print_exit(NULL, shell, "Outfile access error", 1);
			}
			if (cmd->redir_out_type[i] == REDIR_OUT)
			{
				unlink(cmd->redir_out[i]);
				cmd->fds_out[i] = open(cmd->redir_out[i], O_CREAT | O_WRONLY,
						0644);
			}
			else if (cmd->redir_out_type[i] == APPEND)
			{
				cmd->fds_out[i] = open(cmd->redir_out[i], O_APPEND | O_CREAT
						| O_WRONLY,
						0644);
			}
			if (cmd->fds_out[i] < 0)
			{
				close_pipes(shell);
				close_fds(shell, cmd->fds_out, i);
				print_exit(NULL, shell, "Outfile couldn't be opened", 1);
			}
			i++;
		}
	}
}

void	open_infiles(t_chunk *cmd, t_minishell *shell)
{
	int		i;
	char	*filename;

	i = 0;
	if (cmd->redir_in)
	{
		while (cmd->redir_in[i])
		{
			if (access(cmd->redir_in[i], F_OK) == 0
				&& access(cmd->redir_in[i], R_OK) == -1)
			{
				close_pipes(shell);
				close_fds(shell, cmd->fds_in, i);
				close_fds(shell, cmd->fds_out, cmd->redir_out_count);
				print_exit(NULL, shell, "Infile access error", 1);
			}
			if (cmd->redir_in_type[i] == REDIR_IN)
				cmd->fds_in[i] = open(cmd->redir_in[i], O_RDONLY, 0644);
			else if (cmd->redir_in_type[i] == HEREDOC)
			{
				filename = ft_strjoin(cmd->redir_in[i], ".heredoc.tmp");
				cmd->fds_in[i] = open(filename, O_CREAT | O_WRONLY, 0600);
				heredoc(cmd->fds_in[i], cmd->redir_in[i]);
				close(cmd->fds_in[i]);
				cmd->fds_in[i] = open(filename, O_RDONLY, 0644);
				unlink(filename);
				free(filename);
			}
			if (cmd->fds_in[i] < 0)
			{
				close_pipes(shell);
				close_fds(shell, cmd->fds_in, i);
				close_fds(shell, cmd->fds_out, cmd->redir_out_count);
				print_exit(NULL, shell, "Infile couldn't be opened", 1);
			}
			i++;
		}
	}
}

void	set_redirects(t_chunk *cmd, t_minishell *shell)
{
	cmd->redir_in_count = set_redir_counts(cmd->redir_in);
	cmd->redir_out_count = set_redir_counts(cmd->redir_out);
	if (cmd->redir_in_count != 0)
		cmd->fds_in = ft_calloc (sizeof(int), cmd->redir_in_count);
	if (cmd->redir_in_count != 0 && !cmd->fds_in)
		printf("we have a situation. abort. :/ \n"); //fix
	if (cmd->redir_out_count != 0)
		cmd->fds_out = ft_calloc (sizeof(int), cmd->redir_out_count);
	if (cmd->redir_out_count != 0 && !cmd->fds_out)
		printf("we have a situation. abort. :/ \n"); //fix
	open_outfiles(cmd, shell);
	open_infiles(cmd, shell);
}
