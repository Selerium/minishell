/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/09/27 15:55:09 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;
	char 	*env_name;

	i = 1;
	start = 1;
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	env_name = ft_substr(input, start, i - start);
	return (env_name);
}

char	*replace_env(char *input, size_t *idx, char *var_name, t_env *env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*final;

	tmp1 = ft_substr(input, 0, *idx);
	if (!env)
		tmp2 = ft_strdup("");
	else 
		tmp2 = ft_strdup(env->value);
	tmp3 = ft_substr(input, *idx + ft_strlen(var_name) + 1, ft_strlen(input)
			- *idx - ft_strlen(var_name) - 1);
	(*idx) += ft_strlen(tmp2) - 1;
	final = ft_strjoin(tmp1, tmp2);
	free (input);
	input = ft_strjoin(final, tmp3);
	free (tmp1);
	free (tmp2);
	free (tmp3);
	free (final);
	return (input);
}

char	*expand_env(char *input, t_minishell shell)
{
	char	*name;
	t_env	*val;
	int		qflag;
	size_t	i;

	i = 0;
	while (input[i])
	{
		qflag = is_quotes_closed(qflag, input[i]);
		if (input[i] == '$' && qflag != 1)
		{
			name = get_env_name(input + i);
			val = get_env(name, shell);
			input = replace_env(input, &i, name, val);
		}
		if (input[i])
			i++;
	}
	return (input);
}

void	expand_tokens(char **args, t_minishell shell)
{
	size_t	i;

	i = 0;
	while (args && args[i])
	{
		args[i] = expand_env(args[i], shell);
		args[i] = trim_quotes(args[i]);
		i++;
	}
}

/*go through each node in linked list*/
/*go through each array
	if string contains '$'
	check if its inside quotes,
	if DOUBLE
		return env value
	if SINGLE
		return literal string
	then check if env var exists
	if exists
		replace with env value
	if not
		return empty string
	*/