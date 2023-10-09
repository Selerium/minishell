/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:48:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/09 21:23:50 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	heredoc(int fd, char *delimiter, t_minishell shell)
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
		text = expand_env(text, shell, 0);
		write(fd, text, ft_strlen(text));
		write(fd, "\n", 1);
		wrap_free(text);
	}
}

bool	open_outfiles(t_chunk *cmd, t_minishell *shell)
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
				printf("Outfile access error\n");
				g_exitcode = 1;
				return (false);
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
				printf("Outfile access error\n");
				g_exitcode = 1;
				return (false);
			}
			i++;
		}
	}
	return (true);
}

bool	open_infiles(t_chunk *cmd, t_minishell *shell)
{
	int		i;
	char	*filename;

	i = 0;
	if (cmd->redir_in)
	{
		while (cmd->redir_in[i])
		{
			if (access(cmd->redir_in[i], F_OK) == 0
				&& cmd->redir_in_type[i] != HEREDOC
				&& access(cmd->redir_in[i], R_OK) == -1)
			{
				close_pipes(shell);
				close_fds(shell, cmd->fds_in, i);
				close_fds(shell, cmd->fds_out, cmd->redir_out_count);
				g_exitcode = 1;
				printf("Infile access error\n");
				return (false);
			}
			if (cmd->redir_in_type[i] == REDIR_IN)
				cmd->fds_in[i] = open(cmd->redir_in[i], O_RDONLY, 0644);
			else if (cmd->redir_in_type[i] == HEREDOC)
			{
				filename = ft_strjoin(cmd->redir_in[i], ".heredoc.tmp");
				cmd->fds_in[i] = open(filename, O_CREAT | O_WRONLY, 0600);
				heredoc(cmd->fds_in[i], cmd->redir_in[i], *shell);
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
				g_exitcode = 1;
				printf("Infile couldn't be opened\n");
				return (false);
			}
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
		printf("we have a situation. abort. :/ \n"); //fix
	if (cmd->redir_out_count != 0)
		cmd->fds_out = ft_calloc (sizeof(int), cmd->redir_out_count);
	if (cmd->redir_out_count != 0 && !cmd->fds_out)
		printf("we have a situation. abort. :/ \n"); //fix
	return (open_outfiles(cmd, shell) && open_infiles(cmd, shell));
}
