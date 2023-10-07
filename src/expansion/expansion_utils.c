/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebucoy <jebucoy@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/07 20:27:35 by jebucoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_exit_code(char *input)
{
	size_t	i;
	char	*exit_code;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	exit_code = NULL;
	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?')
		{
			exit_code = ft_itoa(g_exitcode, 0, 0);
			tmp = ft_substr(input, 0, i);
			printf("tmp: %s\n", tmp);
			tmp2 = ft_substr(input, i + 2, ft_strlen(input) - ft_strlen(tmp));
			printf("tmp2: %s\n", tmp2);
			tmp3 = ft_strjoin(tmp, exit_code);
			printf("tmp3: %s\n", tmp3);
			free(input);
			input = ft_strjoin(tmp3, tmp2);
			free(exit_code);
			free(tmp);
			free(tmp2);
			free(tmp3);
			return (input);
		}
		i++;
	}
	return (input);
}

char	*get_env_name(char *input)
{
	size_t	i;
	size_t	start;
	char	*env_name;

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
		qflag = get_quote_type(qflag, input[i]);
		if (input[i] == '$' && qflag != 1)
		{
			if (input[i + 1] == '?')
				i += 2;
			name = get_env_name(input + i);
			val = get_env(name, shell);
			input = replace_env(input, &i, name, val);
		}
		if (input[i])
			i++;
	}
	input = get_exit_code(input);
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