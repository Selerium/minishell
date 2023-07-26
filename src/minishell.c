/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:57:20 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/23 20:36:21 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"
#include <readline/history.h>

/**
*	free the envs list safely (i think).
*/
void	free_envs(t_env *envs)
{
	t_env	*next;

	while (envs)
	{
		free(envs->name);
		free(envs->value);
		next = envs->next;
		free(envs);
		envs = next;
	}
}

t_cmd	*set_cmd(char	*cmd)
{
	t_cmd	*newcmd;
	char	**parts;
	int		i;

	newcmd = (t_cmd *) malloc (sizeof(t_cmd));
	parts = ft_split(cmd, ' ');
	i = 0;
	while (parts[i])
	{
		if (parts[i][0] == '<')
			newcmd->infile = parts[i];
		else if (parts[i][0] == '>')
			newcmd->outfile = parts[++i];
		else
			newcmd->cmd = parts[i];
		i++;
	}
	return (newcmd);
}

t_cmd	*parse(char *str)
{
	t_cmd	*cmd;
	t_cmd	*next;
	char	**cmds;
	int		i;

	cmd = (t_cmd *) malloc (sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmds = ft_split(str, '|');
	cmd = set_cmd(*cmds);
	i = 0;
	next = cmd;
	while (cmds[i])
	{
		next->next = set_cmd(cmds[i++]);
		next = next->next;
	}
	while (--i >= 0)
		free(cmds[i]);
	free (cmds);
	return (cmd);
}

/**
	currently it's just running forever with a prompt and i've added builtins
	to test.
*/
int	main(int argc, char **argv, char **env)
{
	int		flag;
	char	*str;
	t_env	*envs;

	(void) argc;
	(void) argv;
	flag = 1;
	envs = fill_vars(env);
	(void) envs;
	while (flag)
	{
		str = readline("hi bestie $> ");
		add_history(str);
		parse(str);
	}
	free_envs(envs);
}
 