/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:52:38 by jadithya          #+#    #+#             */
/*   Updated: 2023/07/22 15:44:18 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

t_env	*make_lst(char *name, char *value)
{
	t_env	*item;

	item = (t_env *) malloc (sizeof(t_env));
	item->name = name;
	item->value = value;
	item->next = NULL;
	return (item);
}

t_env	*fill_vars(char **env)
{
	int		i;
	int		j;
	int		len;
	t_env	*item;
	t_env	*start;

	j = 0;
	i = 0;
	while (env[i][j] != '=')
		j++;
	len = ft_strlen(env[i]);
	start = make_lst(ft_substr(env[i], 0, j), ft_substr(env[i], j + 1, len));
	item = start;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		len = ft_strlen(env[i]);
		item->next = make_lst(ft_substr(env[i], 0, j),
				ft_substr(env[i], j + 1, len));
		item = item->next;
	}
	item->next = NULL;
	return (start);
}
