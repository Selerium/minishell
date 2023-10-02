/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:48:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/02 18:27:51 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <fcntl.h>
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
		if (ft_strlen(text) == 0)
			continue ;
		if (ft_strncmp(text, delimiter, ft_strlen(text)) == 0)
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
			if (cmd->redir_out_type[i] == REDIR_OUT)
			{
				if (access(cmd->redir_out[i], W_OK | X_OK) == -1)
				{
					close_pipes(shell);
					print_exit(NULL, shell, "Outfile couldn't be opened");
				}
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
				print_exit(NULL, shell, "Outfile couldn't be opened");
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
			if (cmd->redir_in_type[i] == REDIR_IN)
				cmd->fds_in[i] = open(cmd->redir_in[i], O_RDONLY, 0644);
			else if (cmd->redir_in_type[i] == HEREDOC)
			{
				filename = ft_strjoin(cmd->redir_in[i], ".heredoc.tmp");
				cmd->fds_in[i] = open(filename, O_CREAT | O_WRONLY, 0600);
				heredoc(cmd->fds_in[i], cmd->redir_in[i]);
				cmd->fds_in[i] = open(filename, O_RDONLY, 0644);
				unlink(filename);
			}
			if (cmd->fds_in[i] < 0)
			{
				close_pipes(shell);
				print_exit(NULL, shell, "Infile couldn't be opened");
			}
			i++;
		}
	}
}

void	set_redirects(t_chunk *cmd, t_minishell *shell)
{
	int	a;
	int	b;

	a = set_redir_counts(cmd->redir_in);
	b = set_redir_counts(cmd->redir_out);
	if (a != 0)
		cmd->fds_in = ft_calloc (sizeof(int), a);
	if (a != 0 && !cmd->fds_in)
		printf("we have a situation. abort. :/ \n");
	if (b != 0)
		cmd->fds_out = ft_calloc (sizeof(int), b);
	if (b != 0 && !cmd->fds_out)
		printf("we have a situation. abort. :/ \n");
	open_outfiles(cmd, shell);
	open_infiles(cmd, shell);
}
