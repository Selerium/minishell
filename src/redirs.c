/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:48:17 by jadithya          #+#    #+#             */
/*   Updated: 2023/10/11 15:03:55 by jadithya         ###   ########.fr       */
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

void	heredoc_sig(int x)
{
	(void) x;
	write(1, "\0", 1);
}

void	heredoc(int fd, char *delimiter, t_minishell shell)
{
	char	*text;
	void	*s1;

	s1 = signal(SIGINT, heredoc_sig);
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
	signal(SIGINT, s1);
}

bool	exit_outfiles(t_minishell *shell, t_chunk *cmd, int i)
{
	close_pipes(shell);
	close_fds(shell, cmd->fds_out, i);
	close_fds(shell, cmd->fds_in, cmd->redir_in_count);
	printf("Outfile access error\n");
	g_exitcode = 1;
	return (false);
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
				return (exit_outfiles(shell, cmd, i));
			if (cmd->redir_out_type[i] == REDIR_OUT)
			{
				unlink(cmd->redir_out[i]);
				cmd->fds_out[i] = open(cmd->redir_out[i], O_CREAT | O_WRONLY,
						0644);
			}
			else if (cmd->redir_out_type[i] == APPEND)
				cmd->fds_out[i] = open(cmd->redir_out[i], O_APPEND | O_CREAT
						| O_WRONLY, 0644);
			if (cmd->fds_out[i] < 0)
				return (exit_outfiles(shell, cmd, i));
			i++;
		}
	}
	return (true);
}
