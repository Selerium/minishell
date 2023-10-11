/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:02:58 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 21:32:58 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	exit_infiles(t_minishell *shell, t_chunk *cmd, int i, char *msg)
{
	close_pipes(shell);
	close_fds(shell, cmd->fds_in, i);
	g_exitcode = 1;
	printf("%s", msg);
	return (false);
}

void	open_heredoc(t_chunk *cmd, t_minishell *shell, int i)
{
	char	*filename;

	filename = ft_strjoin(cmd->redir_in[i], ".heredoc.tmp");
	cmd->fds_in[i] = open(filename, O_CREAT | O_WRONLY, 0600);
	heredoc(cmd->fds_in[i], cmd->redir_in[i], *shell);
	close(cmd->fds_in[i]);
	cmd->fds_in[i] = open(filename, O_RDONLY, 0644);
	unlink(filename);
	free(filename);
}

bool	open_infiles(t_chunk *cmd, t_minishell *shell)
{
	int		i;

	i = 0;
	if (cmd->redir_in)
	{
		while (cmd->redir_in[i])
		{
			if (access(cmd->redir_in[i], F_OK) == 0
				&& cmd->redir_in_type[i] != HEREDOC
				&& access(cmd->redir_in[i], R_OK) == -1)
				return exit_infiles(shell, cmd, i, "Infile access error\n");
			if (cmd->redir_in_type[i] == REDIR_IN)
				cmd->fds_in[i] = open(cmd->redir_in[i], O_RDONLY, 0644);
			else if (cmd->redir_in_type[i] == HEREDOC)
				open_heredoc(cmd, shell, i);
			if (cmd->fds_in[i] < 0)
				return exit_infiles(shell, cmd, i, "Infile couldn't be opened\n");
			i++;
		}
	}
	return (true);
}

bool	set_redirects(t_chunk *cmd, t_minishell *shell)
{
	cmd->redir_in_count = set_redir_counts(cmd->redir_in);
	cmd->redir_out_count = set_redir_counts(cmd->redir_out);
	if (cmd->redir_in_count != 0)
		cmd->fds_in = ft_calloc (sizeof(int), cmd->redir_in_count);
	if (cmd->redir_in_count != 0 && !cmd->fds_in)
	{
		printf("we have a situation. abort. :/ \n");
		return (false);
	}
	if (cmd->redir_out_count != 0)
		cmd->fds_out = ft_calloc (sizeof(int), cmd->redir_out_count);
	if (cmd->redir_out_count != 0 && !cmd->fds_out)
	{
		printf("we have a situation. abort. :/ \n");
		return (false);
	}
	return (open_infiles(cmd, shell) && open_outfiles(cmd, shell));
}
