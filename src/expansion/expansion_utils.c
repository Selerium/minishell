/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/09 13:06:05 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;
	char	*env_name;

	i = 1;
	start = 1;
	if (input[i] == '?')
		return (ft_strdup("?"));
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	env_name = ft_substr(input, start, i - start);
	return (env_name);
}

char	*replace_env(char *input, size_t *idx, char *var_name, char *env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*final;

	tmp1 = ft_substr(input, 0, *idx);
	if (!env)
		tmp2 = ft_strdup("");
	else
		tmp2 = ft_strdup(env);
	tmp3 = ft_substr(input, *idx + ft_strlen(var_name) + 1, ft_strlen(input)
			- *idx - ft_strlen(var_name) - 1);
	printf("tmp1: %s\n", tmp1);
	printf("tmp2: %s\n", tmp2);
	printf("tmp3: %s\n", tmp3);
	(*idx) += ft_strlen(tmp2) - 1;
	if (!env)
		(*idx)++;
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
	char	*val;
	int		qflag;
	size_t	i;

	i = 0;
	qflag = 0;
	while (input[i])
	{
		qflag = get_quote_type(qflag, input[i]);
		if (input[i] == '$' && input[i + 1] && !ft_isspace(input[i + 1]) && (input[i + 1]  != SINGLE && input[i + 1]  != DOUBLE) && qflag != 1)
		{
			name = get_env_name(input + i);
			if (!ft_strncmp(name, "?", 1))
				val = ft_itoa(g_exitcode, 0, 0);
			else
			{
				t_env *env_var = get_env(name, shell);
				if (env_var)
					val = ft_strdup(env_var->value);
				else
					val = NULL;
			}
			input = replace_env(input, &i, name, val);
			wrap_free(name);
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
