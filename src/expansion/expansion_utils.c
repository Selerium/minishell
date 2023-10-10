/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:17:59 by jebucoy           #+#    #+#             */
/*   Updated: 2023/10/10 18:39:13 by jadithya         ###   ########.fr       */
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
		tmp2 = env;
	tmp3 = ft_substr(input, *idx + ft_strlen(var_name) + 1, ft_strlen(input)
			- *idx - ft_strlen(var_name) - 1);
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

char	*check_val_conds(char *val, char *name, t_minishell shell)
{
	t_env	*env_var;

	env_var = NULL;
	if (!ft_strncmp(name, "?", 1))
		val = ft_itoa(g_exitcode, 0, 0);
	else
	{
		env_var = get_env(name, shell);
		if (env_var)
			val = ft_strdup(env_var->value);
		else
			val = NULL;
	}
	return (val);
}

char	*expand_env(char *input, t_minishell shell, int qflag)
{
	char	*name;
	char	*val;
	size_t	i;
	bool	flag;

	i = 0;
	flag = true;
	val = NULL;
	while (ft_strlen(input) && input[i])
	{
		qflag = get_quote_type(qflag, input[i]);
		if (input[i] == '$' && input[i + 1] && !ft_isspace(input[i + 1])
			&& (input[i + 1] != SINGLE && input[i + 1] != DOUBLE) && qflag != 1)
		{
			name = get_env_name(input + i);
			val = check_val_conds(val, name, shell);
			input = replace_env(input, &i, name, val);
			wrap_free(name);
			flag = false;
		}
		if ((ft_strlen(input) && input[i]) && (flag || (val)))
			i++;
		flag = true;
	}
	return (input);
}

//type 0 is redir in
//type 1 is redir out
//type 2 is cmd
void	expand_tokens(char **args, t_minishell shell, int type)
{
	size_t	i;

	i = 0;
	while (args && args[i])
	{
		if (!type && shell.cmds->redir_in_type && shell.cmds->redir_in_type[i])
		{
			if (shell.cmds->redir_in_type[i] != HEREDOC)
				args[i] = expand_env(args[i], shell, 0);
		}
		else
			args[i] = expand_env(args[i], shell, 0);
		args[i] = trim_quotes(args[i]);
		i++;
	}
}
