/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:18:09 by jadithya          #+#    #+#             */
/*   Updated: 2022/09/17 16:18:09 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

char	*ft_wrapjoin(char *str1, char *str2)
{
	char	*newstr;

	newstr = ft_strjoin(str1, str2);
	free (str1);
	return (newstr);
}

char	*ft_findpath(t_env *paths, char *cmd)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (paths->value[i])
	{
		j = 0;
		while (paths->value[i + j] && paths->value[i + j] != ':')
			j++;
		path = ft_substr(paths->value, i, j);
		if (path[ft_strlen(path) - 1] != '/')
			path = ft_wrapjoin(path, "/");
		path = ft_wrapjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		if (paths->value[i + j] == '\0')
			break ;
		i += (j + 1);
	}
	return (NULL);
}

char	*ft_findcmd(char *cmd, t_env *env)
{
	char	*path;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		path = ft_strdup(cmd);
		return (path);
	}
	while (env)
	{
		if (ft_strnstr(env->name, "PATH", 4) != NULL)
			break ;
		env = env->next;
	}
	path = ft_findpath(env, cmd);
	return (path);
}

// int	main(int argc, char **argv, char **env)
// {
// 	if (argc && argv) {}
// 	ft_printf("%s\n", ft_findcmd("ls", env));
// 	return (0);
// }