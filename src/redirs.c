/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:48:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/09/11 14:50:55 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <fcntl.h>
#include <stdio.h>
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

void	open_outfiles(t_chunk *cmd)
{
	int	i;

	i = 0;
	if (cmd->redir_out)
	{
		while (cmd->redir_out[i])
		{
			if (cmd->redir_out_type[i] == REDIR_OUT)
			{
				unlink(cmd->redir_out[i]);
				cmd->fds_out[i] = open(cmd->redir_out[i], O_CREAT | O_WRONLY,
						0644);
			}
			else if (cmd->redir_out_type[i] == APPEND)
			{
				cmd->fds_out[i] = open(cmd->redir_out[i], O_APPEND | O_CREAT,
						0644);
			}
			i++;
		}
	}
}

void	heredoc(int fd, char *delimiter)
{
	char	*text;

	while (true)
	{
		printf("[%s] heredoc> ", delimiter);
		text = readline("");
		if (ft_strncmp(text, delimiter, ft_strlen(text)) == 0)
			break ;
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
	}
}

void	open_infiles(t_chunk *cmd)
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
			i++;
		}
	}
}

void	set_redirects(t_chunk *cmd)
{

	cmd->fds_in = malloc (sizeof(int) * set_redir_counts(cmd->redir_in));
	cmd->fds_out = malloc (sizeof(int) * set_redir_counts(cmd->redir_out));
	open_outfiles(cmd);
	open_infiles(cmd);
}